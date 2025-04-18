//
// Created by shun on 4/18/25.
//

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/traffic-control-module.h"
#include "ns3/log.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("DrrSimulation");

int main(int argc, char *argv[]) {
  double stopTime = 20.0;
  uint32_t queueSize = 100;

  NodeContainer hosts, router;
  hosts.Create(2);       // host0: sender, host1: receiver
  router.Create(1);      // router: drr-enabled

  // Create p2p links
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("4Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("1ms"));

  // host0 <-> router
  NetDeviceContainer d1 = p2p.Install(hosts.Get(0), router.Get(0));

  // router <-> host1
  p2p.SetDeviceAttribute("DataRate", StringValue("1Mbps")); // bottleneck
  NetDeviceContainer d2 = p2p.Install(router.Get(0), hosts.Get(1));

  // Add DRR Queue to bottleneck link
  TrafficControlHelper tch;
  tch.SetRootQueueDisc("ns3::DrrQueue",
                       "MaxPackets", UintegerValue(queueSize),
                       "Quantum", StringValue("300:200:100")); // 3:2:1 ratio
  tch.Install(d2.Get(0)); // router's outbound to host1

  // Install stack
  InternetStackHelper internet;
  internet.InstallAll();

  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer if1 = ipv4.Assign(d1);
  ipv4.SetBase("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer if2 = ipv4.Assign(d2);

  // Port numbers
  uint16_t ports[3] = {50000, 50001, 50002};

  // BulkSend from host0 to host1
  for (int i = 0; i < 3; ++i) {
    BulkSendHelper bulk("ns3::TcpSocketFactory",
                        InetSocketAddress(if2.GetAddress(1), ports[i]));
    bulk.SetAttribute("MaxBytes", UintegerValue(0));
    ApplicationContainer app = bulk.Install(hosts.Get(0));
    app.Start(Seconds(0.0));
    app.Stop(Seconds(stopTime));

    PacketSinkHelper sink("ns3::TcpSocketFactory",
                          InetSocketAddress(Ipv4Address::GetAny(), ports[i]));
    ApplicationContainer sinkApp = sink.Install(hosts.Get(1));
    sinkApp.Start(Seconds(0.0));
    sinkApp.Stop(Seconds(stopTime));
  }

  Simulator::Stop(Seconds(stopTime));
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}