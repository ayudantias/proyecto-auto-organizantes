#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/position-allocator.h"
#include "ns3/config-store-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/flow-monitor-module.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

NS_LOG_COMPONENT_DEFINE ("Adhoc");

using namespace ns3;

int main (int argc, char *argv[]) {
  /*
   * Simulation parameters
   */
  std::string phyMode ("DsssRate1Mbps");

  uint32_t numNodes = 3;      // number of nodes
  int flows = numNodes * 15;   // number of flows
  int packetSizeMean = 750;  // Bytes for rand variable
  int dataRate = 1024;        // Kbps bandwidth
  double totalTime = 60.0;    // simulation time seconds

  CommandLine cmd;
  cmd.AddValue ("numNodes", "Number of nodes", numNodes);
  cmd.AddValue ("flows", "Number of flows", flows);
  cmd.AddValue ("packetSizeMean", "Mean for packetSize with exp distribution", packetSizeMean);
  cmd.AddValue ("dataRate", "Bandwith of channels", dataRate);
  cmd.AddValue ("totalTime", "Simulation time", totalTime);
  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
  cmd.Parse (argc, argv);

  // Node creation
  NodeContainer nodes;
  nodes.Create (numNodes);

  // Wifi configuration
  WifiHelper wifi;
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  YansWifiChannelHelper wifiChannel;
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel");
  wifiPhy.SetChannel (wifiChannel.Create ());
  WifiMacHelper wifiMac;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                "DataMode",StringValue (phyMode),
                                "ControlMode",StringValue (phyMode));
  // Set it to adhoc mode
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, nodes);

  /* With FriisPropagationLossModel, positions below are
   * used for received signal strength.
   */

  /*
   * Mobility model
   */
  MobilityHelper mobility;
  // Locate nodes in a grid
  ObjectFactory position;
  position.SetTypeId ("ns3::GridPositionAllocator");
  position.Set ("MinX", DoubleValue (0.0));
  position.Set ("MinY", DoubleValue (0.0));
  position.Set ("DeltaX", DoubleValue (20));
  position.Set ("DeltaY", DoubleValue (20));
  position.Set ("GridWidth", UintegerValue (sqrt (numNodes)));
  position.Set ("LayoutType", StringValue ("RowFirst"));
  Ptr<PositionAllocator> PositionAlloc = position.Create ()->GetObject<PositionAllocator> ();
  mobility.SetPositionAllocator (PositionAlloc);
  // Defines how nodes move through space
  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                             "Speed", StringValue ("ns3::ExponentialRandomVariable[Mean=3]"),
                             "Pause", StringValue ("ns3::ExponentialRandomVariable[Mean=5]"),
                             "PositionAllocator", PointerValue (PositionAlloc));
  mobility.Install (nodes);
  
  //Enable OLSR
  OlsrHelper olsr;  
  InternetStackHelper internet;
  internet.SetRoutingHelper (olsr); // has effect on the next Install ()
  internet.Install (nodes);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer ifcont = ipv4.Assign (devices);

  /*
   * Random Traffic- (Poisson Model)
   */
  int min = 0;
  int max = nodes.GetN ();
  // Random variable for node selection
  Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
  x->SetAttribute ("Min", DoubleValue (min));
  x->SetAttribute ("Max", DoubleValue (max));
  // Random variable for flow's packets size
  Ptr<ExponentialRandomVariable> size = CreateObject<ExponentialRandomVariable> ();
  size->SetAttribute ("Mean", DoubleValue (packetSizeMean));
  // DataRate conversion to stringstream
  std::ostringstream stringDataRate;
  stringDataRate << dataRate;

  // Creation of traffic flows
  std::cout << "Flows" << std::endl;
  for (uint32_t i = 0; (int) i < flows; i++) {
      int source = i % numNodes, sink = source;
      while (sink == source) {
          sink = x->GetValue ();
      }
      int packSize =  size->GetValue();
      while (packSize == 0) {
          packSize =  size->GetValue();
      }
      std::cout << "Source = " << source << " Sink = " << sink << " Size = " << packSize << std::endl;
      // Traffic generator
      OnOffHelper onoff ("ns3::UdpSocketFactory", InetSocketAddress (ifcont.GetAddress (sink), 9));
      onoff.SetAttribute ("OnTime", StringValue ("ns3::ExponentialRandomVariable[Mean=0.01]"));
      onoff.SetAttribute ("OffTime", StringValue ("ns3::ExponentialRandomVariable[Mean=3]"));
      onoff.SetAttribute ("PacketSize", UintegerValue (packSize));
      onoff.SetAttribute ("DataRate", StringValue (stringDataRate.str() + "Kbps"));
      ApplicationContainer temp = onoff.Install (nodes.Get (source));
  }

  // Tracing
  wifiPhy.EnablePcap ("adhoc", devices);

  Simulator::Stop (Seconds (totalTime));

  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

  Simulator::Run ();

  /*
   * FlowMonitor
   */

  uint64_t bytesTotal = 0;
  uint32_t allTx = 0, allRx = 0, allLx = 0;
  double lastRxTime = -1, firstRxTime = -1;
  float allDelay = 0.;

  monitor->CheckForLostPackets ();
  Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
  std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

  for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin (); i != stats.end (); ++i) {
      if (firstRxTime < 0)
        firstRxTime = i->second.timeFirstRxPacket.GetSeconds (); // Find first packet arrival time
      else if (firstRxTime > i->second.timeFirstRxPacket.GetSeconds ())
        firstRxTime = i->second.timeFirstRxPacket.GetSeconds ();

      if (lastRxTime < i->second.timeLastRxPacket.GetSeconds ())
        lastRxTime = i->second.timeLastRxPacket.GetSeconds (); // Find last packet arrival time

      bytesTotal = bytesTotal + i->second.rxBytes;
      bytesTotal += i->second.rxBytes * 8.0 / (lastRxTime - firstRxTime) / 1024;

      allTx += i->second.txPackets;
      allRx += i->second.rxPackets;
      allDelay += i->second.delaySum.GetSeconds () / i->second.rxPackets;
      allLx += i->second.lostPackets;
    }

  /*
   * Desempeño de la red
   */

  std::cout << "Nodes = " << nodes.GetN () << " Sim time = " << totalTime << std::endl
            << "Avg throughput = " << bytesTotal * 8 / (lastRxTime - firstRxTime) / 1024
            << " kbits/sec"
            << " AllTx= " << allTx << " AllRx= " << allRx << " AllLx= " << allLx
            << " TotalDelay= " << allDelay << std::endl;

  Simulator::Destroy ();

  return 0;
}
