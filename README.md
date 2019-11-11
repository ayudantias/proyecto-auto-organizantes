# Diseño de un framework para la construcción de sistemas descentralizados.
En la construcción de esta investigación se han identificado los siguientes aspectos metodológicos: el tipo de estudio que se va a realizar es un estudio de exploración, esto se debe a que se tiene que realizar una búsqueda sobre los temas que encierran los ejes temáticos de la investigación los cuales son sistemas descentralizadas, redes Ad-hoc, redes auto organizantes y técnicas computacionales para sistemas distribuidos.
Se van a considerar cinco grandes fases en el desarrollo del proyecto, estas fases van relacionadas con los objetivos específicos planteados. De manera que se debe tener una secuencia en las fases y al obtener una fase se avance a la otra. Las fases son las siguientes:
1. Conceptualización de los aspectos teóricos que enmarcan los ejes fundamentales de la investigación, sistemas descentralizados, sistemas auto-organizartes y computación distribuida.
2. Diseño de la metodología de desarrollo del framework para sistemas descentralizados: tomando como referencias diferentes metodologías de la literatura, llegar a la consolidación de una metodología apropiada para la generación de técnicas de computación para el desarrollo de sistemas descentralizados artificiales.
3. Construcción de los módulos requeridos para la consecución del sistema. Estos módulos deben contener los aspectos: redes ad hoc, sistemas de agentes de software. Hacer un listado de los componentes y sus propiedades para tener escenarios de pruebas convenientes con los objetivos de la investigación.
4. Implementación de un set de pruebas de los módulos para garantizar un buen proceso de implementación. Esta implementación debe ir en dirección de tres escenarios:
  - Escenario 1: una red ad hoc, con la capacidad para la implementación de scripts de gestión.
  - Escenario 2: un sistema de agentes de software para implementar comunicaciones entre agentes.
  - Escenario 3: un prototipo de framework que permita la implementación de diferentes soluciones a redes de comunicaciones, extensión de cobertura, redes de sensores. 
5. Construcción de un set de pruebas con una red ad hoc implementada con nodos computacionales para analizar su comportamiento aplicando los mecanismos de gestión de redes. Se debe realizar la prueba con una red de nodos físicos (Raspberry pi) y realizar mediciones de throughput, tiempo de espera y numero de paquetes perdidos.
 Las anteriores fases, son los pasos a seguir para la consecución del objetivo general de la investigación que se propone. 
 
 # Descripción de la simulación
 
 Consiste en una red ad hoc conformada por 4 nodos que tienen movimiento y tráfico variable, donde todos los nodos generan tráfico.
# Importación de librerías
```c++
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
```
Se establece el número de nodos, el número de flujos o conexiones, la media de tamaño del paquete, el ancho de banda y el tiempo total de simulación.

```c++
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
```
Se parametriza la simulación desde la línea de comandos cmd.AddValue() imprime los valores de cada variable. El segundo parámetro es una descripción.

Se crean los nodos.

```c++
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

```
WifiHelper ayuda a crear objetos WifiNetDevide y a configurar sus atributos.
YansWifiPhyHelper crea un ayudante de Phy con la configuración por defecto.
YansWifiChannelHelper crea un canal llamado wifiChannel.
Se modela la demora y pérdida de propagación a través de un medio de transmisión.
en wifiChannel.  
```c++
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
```
Se asigna el canal al objeto wifiPhy.
Se crean capas MAC. 
Se define el standard 802.11b.

```c++
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
```

| ............. | ............. | 802.11 Wireless Standards | ............. | ............. | ............. | 
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
|IEEE Standard|802.11a|802.11b|802.11g|802.11n|802.11ac|
|Year Adopted|1999|1999|2003|2009|2014|
|Frecuency|5GHz|2.4GHz|2.4GHz|2.4/5GHz|5GHz|
|Max. Data Rate|54 Mbps|11 Mbps|54 Mbps|600 Mbps|1 Gbps|
|Typical Range Indoors*|100 ft.|100ft.|125ft.|225ft.|90ft.|
|Typical Range Outdoors*|400 ft.|450 ft.|450 ft.|825 ft.|1,000 ft.|

Se establece el modo ad hoc.


```c++
  // Set it to adhoc mode
  wifiMac.SetType ("ns3::AdhocWifiMac");
  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, nodes);
```
MobilityHelper es una clase auxiliar utilizada para asignar posiciones y modelos de movilidad a nodos.
GridPositionAllocator asigna posiciones en una cuadrícula 2d rectangular.

```c++
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
```
PositionAllocator asigna  un conjunto de posiciones.
SetMobilityModel define cómo se mueven los nodos a través del espacio.  En este caso es de manera aleatoria.

```c++
  Ptr<PositionAllocator> PositionAlloc = position.Create ()->GetObject<PositionAllocator> ();
  mobility.SetPositionAllocator (PositionAlloc);
  // Defines how nodes move through space
  mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                             "Speed", StringValue ("ns3::ExponentialRandomVariable[Mean=3]"),
                             "Pause", StringValue ("ns3::ExponentialRandomVariable[Mean=5]"),
                             "PositionAllocator", PointerValue (PositionAlloc));
  mobility.Install (nodes);
```
Optimized Link State Routing (OLSR) es un protocolo de enrutamiento, que trabaja en forma distribuida para establecer las conexiones entre los nodos en una red inalámbrica ad hoc.
InternetStackHelper agrega la funcionalidad IP / TCP / UDP a los nodos existentes.
Se realiza la asignación simple de direcciones IPv4.

```c++
  //Enable OLSR
  OlsrHelper olsr;  
  InternetStackHelper internet;
  internet.SetRoutingHelper (olsr); // has effect on the next Install ()
  internet.Install (nodes);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer ifcont = ipv4.Assign (devices);
```
UniformRandomVariable: Se crean dos variables aleatorias, “x” y “size” con sus respectivos parámetros.
```c++
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
```
OnOffHelper: Instancia una generador de tráfico con un patrón on/off  que alterna entre ambos estados de acuerdo a los parámetros OnTime y OffTime.
```c++
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
```
*EnablePcap*: Activa el output pcap en los dispositivos.
*FlowMonitorHelper*: Activa el monitoreo del flujo IP en el conjunto de nodos.

```c++
  // Tracing
  wifiPhy.EnablePcap ("adhoc", devices);

  Simulator::Stop (Seconds (totalTime));

  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

  Simulator::Run ();
```
*CheckForLostPackets*: Verifica paquetes que aparentan haberse perdido.
*Ipv4FlowClassifier*: Clasifica los paquetes según encabezados TCP/UDP y la IP.

```c++
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
```
Se realiza el cálculo de las estadísticas.

```c++
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
```
Se imprime la información general y resultados .

```c++
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
```
