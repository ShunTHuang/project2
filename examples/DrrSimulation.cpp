//
// Created by shun on 4/18/25.
//

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/log.h"
#include "queue/DeficitRoundRobin.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("DrrSimulation");

int main(int argc, char *argv[]) {
    if (argc < 2)
    {
        std::cerr << "Usage: ./ns3 run DrrSimulation -- <config-file-path>\n";
        return 1;
    }

    std::string configFile = argv[1];

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
    NetDeviceContainer dOut = p2pOut.Install(router.Get(0), hosts.Get(1));

    Ptr<DeficitRoundRobin> drr = CreateObject<DeficitRoundRobin>();
    drr->SetAttribute("ConfigFile", StringValue(configFile));
    drr->Initialize();

    Ptr<NetDevice> dev = dOut.Get(0);
    Ptr<PointToPointNetDevice> ptpDev = DynamicCast<PointToPointNetDevice>(dev);
    ptpDev->SetQueue(drr);
    ptpDev->AggregateObject(drr);

    // Add DRR Queue to bottleneck link
    InternetStackHelper internet;
    internet.Install(hosts);
    internet.Install(router);

    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer ifHigh = ipv4.Assign(dIn);
    ipv4.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer ifLow = ipv4.Assign(dOut);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    // Port numbers
    uint16_t ports[3] = {50001, 50002, 50003};
    ApplicationContainer sinkApps;

    // BulkSend from host0 to host1
    for (int i = 0; i < 3; ++i) {
        PacketSinkHelper udpSink("ns3::UdpSocketFactory",
                                 InetSocketAddress(Ipv4Address::GetAny(), ports[i]));
        ApplicationContainer sinkApp = udpSink.Install(hosts.Get(1));
        sinkApp.Start(Seconds(0.0));
        sinkApp.Stop(Seconds(stopTime));
        sinkApps.Add(sinkApp);

        OnOffHelper udpClient("ns3::UdpSocketFactory",
                              InetSocketAddress(ifLow.GetAddress(1), ports[i]));
        udpClient.SetAttribute("DataRate", DataRateValue(DataRate("4Mbps")));
        udpClient.SetAttribute("PacketSize", UintegerValue(270));
        udpClient.SetAttribute("StartTime", TimeValue(Seconds(0.0)));
        udpClient.SetAttribute("StopTime", TimeValue(Seconds(stopTime)));
        ApplicationContainer clientApp = udpClient.Install(hosts.Get(0));
    }

    p2pIn.EnablePcap("drr-in", dIn.Get(0), 0);
    p2pOut.EnablePcap("drr-out", dOut.Get(0), 0);

    Simulator::Stop(Seconds(stopTime));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}