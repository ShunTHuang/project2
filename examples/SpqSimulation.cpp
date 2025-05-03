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
#include "utils/CLIParser.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SpqSimulation");

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./ns3 run SpqSimulation -- <config-file-path>\n";
        return 1;
    }

    std::string configFile = argv[1];
    LogComponentEnable ("SpqSimulation", LOG_LEVEL_INFO);

    if (configFile.size() >= 4 && configFile.substr(configFile.size() - 4) == ".txt")
    {
        const std::string outputJsonPath = "src/project2/SpqCLIConfig.json";
        CLIParser generator;
        if (!generator.GenerateSpqConfig(configFile, outputJsonPath)) {
            std::cerr << "Failed to generate SPQ config from " << configFile << "\n";
            std::exit(1);
        }
        configFile = outputJsonPath;
    }

    double stopTime = 40.0;

    NodeContainer hosts, routers;
    hosts.Create(2);
    routers.Create(1);

    // 4Mbps，1Mbps
    PointToPointHelper p2pHigh, p2pLow;
    p2pHigh.SetDeviceAttribute("DataRate", StringValue("4Mbps"));
    p2pHigh.SetChannelAttribute("Delay",    StringValue("1ms"));
    p2pLow .SetDeviceAttribute("DataRate", StringValue("1Mbps"));
    p2pLow .SetChannelAttribute("Delay",    StringValue("1ms"));


    // high：host0 <——> router0
    NetDeviceContainer devsHigh = p2pHigh.Install(hosts.Get(0), routers.Get(0));

    // low：router0 <——> host1
    p2pLow.SetQueue("ns3::StrictPriorityQueue<Packet>",
                     "ConfigFile", StringValue(configFile));
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
    //host0  ==> (HIGH, 4Mbps)==>  router ==> (LOW, 1Mbps) ==>  host1
    uint16_t portA = 50000, portB = 50001;

    PacketSinkHelper sinkB("ns3::UdpSocketFactory",
                           InetSocketAddress(Ipv4Address::GetAny(), portB));
    PacketSinkHelper sinkA("ns3::UdpSocketFactory",
                           InetSocketAddress(Ipv4Address::GetAny(), portA));
    ApplicationContainer sinkAppsB = sinkB.Install(hosts.Get(1));
    ApplicationContainer sinkAppsA = sinkA.Install(hosts.Get(1));
    sinkAppsB.Start(Seconds(0.0));
    sinkAppsA.Start(Seconds(0.0));

    OnOffHelper udpB("ns3::UdpSocketFactory",
                     InetSocketAddress(ifLow.GetAddress(1), portB));
    udpB.SetAttribute("OnTime",  StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    udpB.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    udpB.SetAttribute("DataRate", DataRateValue(DataRate("4Mbps")));
    udpB.SetAttribute("PacketSize", UintegerValue(1000));
    ApplicationContainer appB = udpB.Install(hosts.Get(0));
    appB.Start(Seconds(0.0));
    appB.Stop(Seconds(40.0));

    OnOffHelper udpA("ns3::UdpSocketFactory",
                     InetSocketAddress(ifLow.GetAddress(1), portA));
    udpA.SetAttribute("OnTime",  StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    udpA.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    udpA.SetAttribute("DataRate", DataRateValue(DataRate("4Mbps")));
    udpA.SetAttribute("PacketSize", UintegerValue(1000));
    ApplicationContainer appA = udpA.Install(hosts.Get(0));
    appA.Start(Seconds(10.0));
    appA.Stop(Seconds(20.0));
    OnOffHelper udpC("ns3::UdpSocketFactory",
                     InetSocketAddress(ifLow.GetAddress(1), portA));
    udpC.SetAttribute("OnTime",  StringValue("ns3::ConstantRandomVariable[Constant=1]"));
    udpC.SetAttribute("OffTime", StringValue("ns3::ConstantRandomVariable[Constant=0]"));
    udpC.SetAttribute("DataRate", DataRateValue(DataRate("4Mbps")));
    udpC.SetAttribute("PacketSize", UintegerValue(1000));
    ApplicationContainer appC = udpC.Install(hosts.Get(0));
    appC.Start(Seconds(30.0));
    appC.Stop(Seconds(40.0));
    Ptr<NetDevice> host0HighDev = hosts.Get(0)->GetDevice(0);
    p2pHigh.EnablePcap ("Pre_SPQ", host0HighDev,  false );

    p2pLow.EnablePcap ("Post_SPQ", routers.Get(0)->GetDevice(1), false);
    Simulator::Stop(Seconds(stopTime));
    Simulator::Run();

    Simulator::Destroy();

  return 0;
}