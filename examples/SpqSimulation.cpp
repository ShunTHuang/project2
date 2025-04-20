//
// Created by peter on 4/18/25.
//
// SpqSimulation.cc

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/log.h"
#include "ns3/traffic-control-module.h"
#include "ns3/trace-helper.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SpqSimulation");

int main(int argc, char *argv[])
{
  // CommandLine cmd;
  // cmd.Parse(argc, argv);
  LogComponentEnable ("SpqSimulation", LOG_LEVEL_INFO);
  NS_LOG_INFO ("SpqSimulation Start time" << Simulator::Now ());
  double stopTime = 30.0;

  NodeContainer hosts, routers;
  hosts.Create(2);
  routers.Create(1);

  // 4Mbps，1Mbps）
  PointToPointHelper p2pHigh, p2pLow;
  p2pHigh.SetDeviceAttribute("DataRate", StringValue("4Mbps"));
  p2pHigh.SetChannelAttribute("Delay",    StringValue("1ms"));
  p2pLow .SetDeviceAttribute("DataRate", StringValue("1Mbps"));
  p2pLow .SetChannelAttribute("Delay",    StringValue("1ms"));


  p2pHigh.SetQueue("ns3::StrictPriorityQueue",
                     "ConfigFile", StringValue("src/config.example.json"));
  NetDeviceContainer devsHigh = p2pHigh.Install(hosts.Get(0), routers.Get(0));

  p2pLow.SetQueue("ns3::StrictPriorityQueue",
                     "ConfigFile", StringValue("src/config.example.json"));
  NetDeviceContainer devsLow  = p2pLow.Install(routers.Get(0), hosts.Get(1));

  InternetStackHelper internet;
  internet.Install(hosts);
  internet.Install(routers);

  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer ifHigh = ipv4.Assign(devsHigh);

  ipv4.SetBase("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer ifLow  = ipv4.Assign(devsLow);

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  uint16_t portA = 50000, portB = 50001;
  BulkSendHelper bulkB("ns3::TcpSocketFactory",
                       InetSocketAddress(ifLow.GetAddress(1), portB));
  bulkB.SetAttribute("MaxBytes", UintegerValue(0));
  bulkB.SetAttribute ("SendSize", UintegerValue (1000));
  ApplicationContainer appB = bulkB.Install(hosts.Get(0));
  appB.Start(Seconds(0.0));
  appB.Stop(Seconds(stopTime));


  BulkSendHelper bulkA("ns3::TcpSocketFactory",
                       InetSocketAddress(ifHigh .GetAddress(1), portA));
  bulkA.SetAttribute("MaxBytes", UintegerValue(0));
  bulkA.SetAttribute ("SendSize", UintegerValue (1500));
  ApplicationContainer appA = bulkA.Install(hosts.Get(0));
  appA.Start(Seconds(5.0));
  appA.Stop(Seconds(stopTime));

  PacketSinkHelper sinkB("ns3::TcpSocketFactory",
                         InetSocketAddress(Ipv4Address::GetAny(), portB));
  PacketSinkHelper sinkA("ns3::TcpSocketFactory",
                         InetSocketAddress(Ipv4Address::GetAny(), portA));
  ApplicationContainer sinkApps;
  sinkApps.Add(sinkB.Install(hosts.Get(1)));
  sinkApps.Add(sinkA.Install(hosts.Get(1)));
  sinkApps.Start(Seconds(0.0));
  sinkApps.Stop(Seconds(stopTime));
  AsciiTraceHelper ascii;
  Ptr<OutputStreamWrapper> stream = ascii.CreateFileStream ("src/project2/throughput.tr");
  p2pHigh.EnableAsciiAll (stream);
  p2pLow .EnableAsciiAll (stream);
  Simulator::Stop(Seconds(stopTime));
  Simulator::Run();
  NS_LOG_INFO ("SpqSimulation stop time " << Simulator::Now ());
  Simulator::Destroy();

  return 0;
}