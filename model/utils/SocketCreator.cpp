//
// Created by koichi on 4/20/25.
//

#include "SocketCreator.h"

namespace ns3 {
    std::vector<Ptr<Socket>> SocketCreator::createSocket(const std::string& filename, Ptr<Node> senderNode) {
        std::ifstream in (filename);
        if (!in) {
            NS_ABORT_MSG ("Cannot open JSON config: " << filename);
        }
        nlohmann::json j; in >> j;

        std::vector<Ptr<Socket>> sockets;
        for (auto &q : j.at("queues"))
        {
            std::string proto      = q.value("protocol", GlobalDefaults::DEFAULT_PROTOCOL);
            std::string srcIpStr   = q.value("sourceIp", GlobalDefaults::DEFAULT_SRC_IP);
            uint16_t    srcPort    = q.value("sourcePort", GlobalDefaults::DEFAULT_SRC_PORT);
            std::string dstIpStr   = q.value("destinationIp", GlobalDefaults::DEFAULT_DST_IP);
            uint16_t    dstPort    = q.value("destinationPort", GlobalDefaults::DEFAULT_DST_PORT);

            TypeId factory = (proto == "udp"
                              ? UdpSocketFactory::GetTypeId()
                              : TcpSocketFactory::GetTypeId());

            Ptr<Socket> sock = Socket::CreateSocket(senderNode, factory);
            sock->Bind   (InetSocketAddress (Ipv4Address(srcIpStr.c_str()), srcPort));
            sock->Connect(InetSocketAddress (Ipv4Address(dstIpStr.c_str()), dstPort));

            sockets.push_back(sock);
        }
        return sockets;
    }
}

// How to use the return value "sockets" to define the subnets, BulkSendApplication, PacketSinkHelper"
//
// int main(int argc, char *argv[])
// {
//   // CLI: config file, simulation stop
//   std::string configFile = "src/config.example.json";
//   double stopTime = 30.0;
//   CommandLine cmd;
//   cmd.AddValue("config", "QoS JSON config file name", configFile);
//   cmd.AddValue("stopTime", "Simulation stop time (s)", stopTime);
//   cmd.Parse(argc, argv);
//
//   LogComponentEnable("SpqSimulation", LOG_LEVEL_INFO);
//   NS_LOG_INFO("SpqSimulation start at " << Simulator::Now());
//
//   // Create nodes
//   NodeContainer hosts, routers;
//   hosts.Create(2);
//   routers.Create(1);
//
//   // Setup P2P links with SPQ
//   PointToPointHelper p2pHigh, p2pLow;
//   p2pHigh.SetDeviceAttribute("DataRate", StringValue("4Mbps"));
//   p2pHigh.SetChannelAttribute("Delay",    StringValue("1ms"));
//   p2pHigh.SetQueue("ns3::StrictPriorityQueue");
//
//   p2pLow.SetDeviceAttribute("DataRate", StringValue("1Mbps"));
//   p2pLow.SetChannelAttribute("Delay",    StringValue("1ms"));
//   p2pLow.SetQueue("ns3::StrictPriorityQueue");
//
//   // Install devices
//   NetDeviceContainer devsHigh = p2pHigh.Install(hosts.Get(0), routers.Get(0));
//   NetDeviceContainer devsLow  = p2pLow.Install(routers.Get(0), hosts.Get(1));
//
//   // Install IP stack
//   InternetStackHelper internet;
//   internet.Install(hosts);
//   internet.Install(routers);
//
//   // Configure sockets per queue from JSON
//   std::vector<Ptr<Socket>> sockets = ConfigureSocketsFromJson(configFile, hosts.Get(0));
//
//   // Derive subnets from first socket's local (src) and peer (dst) addresses
//   Ipv4Mask mask("255.255.255.0");
//   // Source subnet
//   InetSocketAddress localInet = InetSocketAddress::ConvertFrom(sockets[0]->GetLocal());
//   Ipv4Address localIp = localInet.GetIpv4();
//   uint32_t netLocal = localIp.Get() & mask.Get();
//   Ipv4Address baseLocal(netLocal);
//   // Destination subnet
//   InetSocketAddress peerInet = InetSocketAddress::ConvertFrom(sockets[0]->GetPeer());
//   Ipv4Address peerIp = peerInet.GetIpv4();
//   uint32_t netPeer = peerIp.Get() & mask.Get();
//   Ipv4Address basePeer(netPeer);
//
//   // Assign subnets based on sockets
//   Ipv4AddressHelper ipv4High;
//   ipv4High.SetBase(baseLocal, mask, localIp);
//   Ipv4InterfaceContainer ifHigh = ipv4High.Assign(devsHigh);
//   Ipv4AddressHelper ipv4Low;
//   ipv4Low.SetBase(basePeer, mask, peerIp);
//   Ipv4InterfaceContainer ifLow  = ipv4Low.Assign(devsLow);
//
//   // Populate routing
//   Ipv4GlobalRoutingHelper::PopulateRoutingTables();
//
//   // Install BulkSendApplications on host0 using sockets
//   ApplicationContainer apps;
//   for (size_t i = 0; i < sockets.size(); ++i) {
//     Ptr<Socket> sock = sockets[i];
//     Ptr<BulkSendApplication> app = CreateObject<BulkSendApplication>();
//     app->SetSocket(sock);
//     app->SetMaxBytes(0);
//     double start = (i == 0 ? 0.0 : 5.0);
//     app->SetStartTime(Seconds(start));
//     app->SetStopTime(Seconds(stopTime));
//     hosts.Get(0)->AddApplication(app);
//     apps.Add(app);
//   }
//
//   // Packet sinks on host1 from sockets
//   ApplicationContainer sinks;
//   for (auto &sock : sockets) {
//     InetSocketAddress peer = InetSocketAddress::ConvertFrom(sock->GetPeer());
//     InetSocketAddress local = InetSocketAddress::ConvertFrom(sock->GetLocal());
//     PacketSinkHelper sink("ns3::TcpSocketFactory",
//                           InetSocketAddress(local.GetIpv4(), peer.GetPort()));
//     auto s = sink.Install(hosts.Get(1));
//     sinks.Add(s);
//   }
//   sinks.Start(Seconds(0.0));
//   sinks.Stop (Seconds(stopTime));
//
//   // Trace
//   AsciiTraceHelper ascii;
//   Ptr<OutputStreamWrapper> stream = ascii.CreateFileStream("throughput.tr");
//   p2pHigh.EnableAsciiAll(stream);
//   p2pLow.EnableAsciiAll(stream);
//
//   Simulator::Stop(Seconds(stopTime));
//   Simulator::Run();
//   Simulator::Destroy();
//   NS_LOG_INFO("SpqSimulation end at " << Simulator::Now());
//   return 0;
// }