//
// Created by koichi on 4/20/25.
//

#ifndef SOCKETCREATOR_H
#define SOCKETCREATOR_H

#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/trace-helper.h"
#include "ns3/traffic-control-module.h"
#include "ns3/socket.h"
#include "GlobalDefaults.h"

namespace ns3 {
    class SocketCreator {
    public:
        static std::vector<Ptr<Socket>> createSocket(const std::string& filename, Ptr<Node> senderNode);
    };
}

#endif //SOCKETCREATOR_H
