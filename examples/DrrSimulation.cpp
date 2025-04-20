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

    LogComponentEnable ("DrrSimulation", LOG_LEVEL_INFO);
    NS_LOG_INFO ("DrrSimulation Start time" << Simulator::Now ());
    double stopTime = 20.0;

    NodeContainer hosts, router;
    hosts.Create(2);       // host0: sender, host1: receiver
    router.Create(1);      // router: drr-enabled

    // 4Mbps，1Mbps）
    PointToPointHelper p2pIn, p2pOut;
    p2pIn .SetDeviceAttribute("DataRate", StringValue("4Mbps"));
    p2pIn .SetChannelAttribute("Delay",    StringValue("1ms"));
    p2pOut.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    p2pOut.SetChannelAttribute("Delay",    StringValue("1ms"));

    // host0 <-> router
    p2pIn.SetQueue("ns3::DeficitRoundRobin", "Quantum", StringValue("300"));
    NetDeviceContainer dIn = p2pIn.Install(hosts.Get(0), router.Get(0));
    // router <-> host1
    p2pOut.SetQueue("ns3::DeficitRoundRobin");
    NetDeviceContainer dOut = p2pOut.Install(router.Get(0), hosts.Get(1));

    // Add DRR Queue to bottleneck link
    InternetStackHelper internet;
    internet.Install(hosts);
    internet.Install(router);

    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer ifHigh = ipv4.Assign(dIn);
    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer iflow = ipv4.Assign(dOut);

    // Port numbers
    uint16_t ports[3] = {50000, 50001, 50002};

    // BulkSend from host0 to host1
    for (int i = 0; i < 3; ++i) {
        BulkSendHelper bulk("ns3::TcpSocketFactory",
                            InetSocketAddress(iflow.GetAddress(1), ports[i]));
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
    NS_LOG_INFO ("DrrSimulation stop time " << Simulator::Now ());
    Simulator::Destroy();

    return 0;
}