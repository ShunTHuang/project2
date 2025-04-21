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
#include "queue/DeficitRoundRobin.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("DrrSimulation");

int main(int argc, char *argv[]) {
    LogComponentEnable ("DrrSimulation", LOG_LEVEL_INFO);
    LogComponentEnable("BulkSendApplication", LOG_LEVEL_INFO);
    LogComponentEnable("PacketSink", LOG_LEVEL_INFO);
    LogComponentEnable("TcpL4Protocol", LOG_LEVEL_INFO);
    LogComponentEnable("TcpSocketBase", LOG_LEVEL_INFO);

    NS_LOG_INFO ("DrrSimulation Start time" << Simulator::Now ());
    double stopTime = 20.0;

    NodeContainer hosts;
    NodeContainer router;
    hosts.Create(2);       // host0: sender, host1: receiver
    router.Create(1);      // router: drr-enabled

    // 4Mbps，1Mbps）
    PointToPointHelper p2pIn;
    PointToPointHelper p2pOut;
    p2pIn .SetDeviceAttribute("DataRate", StringValue("4Mbps"));
    p2pIn .SetChannelAttribute("Delay",    StringValue("1ms"));
    p2pOut.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    p2pOut.SetChannelAttribute("Delay",    StringValue("1ms"));

    // host0 <-> router
    NetDeviceContainer dIn = p2pIn.Install(hosts.Get(0), router.Get(0));
    // router <-> host1
    p2pOut.SetQueue("ns3::DeficitRoundRobin",
                     "ConfigFile", StringValue("src/config.example.json"));
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

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Port numbers
    uint16_t ports[3] = {50001, 50002, 50003};
    ApplicationContainer sinkApps;

    // BulkSend from host0 to host1
    for (int i = 0; i < 3; ++i) {
        BulkSendHelper bulk("ns3::TcpSocketFactory",
                            InetSocketAddress(iflow.GetAddress(1), ports[i]));
        bulk.SetAttribute("MaxBytes", UintegerValue(0));
        bulk.SetAttribute("SendSize", UintegerValue(1500));
        ApplicationContainer app = bulk.Install(hosts.Get(0));
        app.Start(Seconds(0.0));
        app.Stop(Seconds(stopTime));

        PacketSinkHelper sink("ns3::TcpSocketFactory",
                              InetSocketAddress(Ipv4Address::GetAny(), ports[i]));
        ApplicationContainer sinkApp = sink.Install(hosts.Get(1));
        sinkApp.Start(Seconds(0.0));
        sinkApp.Stop(Seconds(stopTime));

        sinkApps.Add(sinkApp);
    }

    p2pOut.EnablePcapAll("drr-out");

    Simulator::Schedule(Seconds(stopTime), [sinkApps, ports]() {
        for (uint32_t i = 0; i < sinkApps.GetN(); ++i) {
            Ptr<PacketSink> sink = DynamicCast<PacketSink>(sinkApps.Get(i));
            if (sink) {
                std::cout << "Port " << ports[i % 3]
                          << " received: " << sink->GetTotalRx()
                          << " bytes" << std::endl;
            }
        }
    });

    Simulator::Stop(Seconds(stopTime));
    Simulator::Run();
    NS_LOG_INFO ("DrrSimulation stop time " << Simulator::Now ());
    Simulator::Destroy();

    return 0;
}