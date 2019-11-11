# Diseño de un framework para la construcción de sistemas descentralizados.
En la construcción de esta investigación se han identificado los siguientes aspectos metodológicos: el tipo de estudio que se va a realizar es un estudio de exploración, esto se debe a que se tiene que realizar una búsqueda sobre los temas que encierran los ejes temáticos de la investigación los cuales son sistemas descentralizadas, redes Ad-hoc, redes auto organizantes y técnicas computacionales para sistemas distribuidos.
Se van a considerar cinco grandes fases en el desarrollo del proyecto, estas fases van relacionadas con los objetivos específicos planteados. De manera que se debe tener una secuencia en las fases y al obtener una fase se avance a la otra. Las fases son las siguientes:
1. Conceptualización de los aspectos teóricos que enmarcan los ejes fundamentales de la investigación, sistemas descentralizados, sistemas auto-organizartes y computación distribuida.
2. Diseño de la metodología de desarrollo del framework para sistemas descentralizados: tomando como referencias diferentes metodologías de la literatura, llegar a la consolidación de una metodología apropiada para la generación de técnicas de computación para el desarrollo de sistemas descentralizados artificiales.
3. Construcción de los módulos requeridos para la consecución del sistema. Estos módulos deben contener los aspectos: redes ad hoc, sistemas de agentes de software. Hacer un listado de los componentes y sus propiedades para tener escenarios de pruebas convenientes con los objetivos de la investigación.
4. Implementación de un set de pruebas de los módulos para garantizar un buen proceso de implementación. Esta implementación debe ir en dirección de tres escenarios:
•	Escenario 1: una red ad hoc, con la capacidad para la implementación de scripts de gestión
•	Escenario 2: un sistema de agentes de software para implementar comunicaciones entre agentes
•	Escenario 3: un prototipo de framework que permita la implementación de diferentes soluciones a redes de comunicaciones, extensión de cobertura, redes de sensores. 
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
Se parametriza la simulación desde la línea de comandos
cmd.AddValue() imprime los valores de cada variable. El segundo parámetro es una descripción.
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
WifiHelper ayuda a crear objetos WifiNetDevide y a configurar sus atributos
YansWifiPhyHelper crea un ayudante de Phy con la configuración por defecto
YansWifiChannelHelper crea un canal llamado wifiChannel
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
Se asigna el canal al objeto wifiPhy
Se crean capas MAC 
Se define el standard 802.11b


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

```c++
```

```c++
```

```c++
```

```c++
```

```c++
```
