//
// Created by koichi on 4/18/25.
//

#include "QoSCreator.h"
#include <fstream>
#include <stdexcept>

#include "../filter_elements/dst_ip.h"
#include "../filter_elements/dst_mask.h"
#include "../filter_elements/src_ip.h"
#include "../filter_elements/src_mask.h"
#include "../filter_elements/src_port.h"
#include "filter_elements/protocol.h"
#include "filter_elements/dst_port.h"
#include "filter_elements/src_port.h"
#include "filter_elements/src_ip.h"
#include "filter_elements/dst_ip.h"
#include "filter_elements/src_mask.h"
#include "filter_elements/dst_mask.h"
#include "queue/StrictPriorityQueue.h"
#include "queue/DeficitRoundRobin.h"

namespace ns3 {

    std::vector<TrafficClass*>
    QoSCreator::CreateTrafficClasses(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Failed to open config file: " + filename);
        }

        json config;
        file >> config;

        std::vector<TrafficClass*> classes;

        for (const auto& q : config["queues"])
        {
            uint32_t priority    = q["priority_level"];
            uint32_t maxPackets  = q["maxPackets"];
            double weight        = q["weight"];
            uint32_t quantum     = q["quantum"];
            bool isDefault       = q["isDefault"];

            auto* tc = new TrafficClass(maxPackets, weight, priority, isDefault, quantum);
            ParseFilters(q["filters"], tc);
            classes.push_back(tc);
        }

        return classes;
    }

    DiffServ*
    QoSCreator::CreateQoS(const std::string& filename)
    {
        auto classes = CreateTrafficClasses(filename);

        std::ifstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Failed to open config file: " + filename);
        }

        json config;
        file >> config;
        std::string mech = config["qos_mechanism"];

        if (mech == "spq")
        {
            return new StrictPriorityQueue(classes);
        }

        if (mech == "drr")
        {
            return new DeficitRoundRobin(classes);
        }

        throw std::invalid_argument("Unknown qos mechanism: " + mech);
    }

    void
    QoSCreator::ParseFilters(const json& filtersConfig, TrafficClass* tc)
    {
        for (const auto& groupJson : filtersConfig)
        {
            auto* group = new Filter();
            for (const auto& f : groupJson)
            {
                std::string type = f["filterType"];

                if (type == "Protocol")
                {
                    std::string proto = f["filterValue"];
                    uint8_t protoNumber = (proto == "tcp") ? 6 : 17;
                    group->AddElement(new Protocol(protoNumber));
                }
                else if (type == "DstPort")
                {
                    group->AddElement(new DstPort(f["filterValue"]));
                }
                else if (type == "SrcPort")
                {
                    group->AddElement(new SrcPort(f["filterValue"]));
                }
                else if (type == "SrcIP")
                {
                    group->AddElement(new SrcIp(Ipv4Address(f["filterValue"].get<std::string>().c_str())));
                }
                else if (type == "DstIP")
                {
                    group->AddElement(new DstIp(Ipv4Address(f["filterValue"].get<std::string>().c_str())));
                }
                else if (type == "SrcMask")
                {
                    std::string addr = f["filterValue"]["address"];
                    std::string mask = f["filterValue"]["mask"];
                    group->AddElement(new SrcMask(Ipv4Address(addr.c_str()), Ipv4Mask(mask.c_str())));
                }
                else if (type == "DstMask")
                {
                    std::string addr = f["filterValue"]["address"];
                    std::string mask = f["filterValue"]["mask"];
                    group->AddElement(new DstMask(Ipv4Address(addr.c_str()), Ipv4Mask(mask.c_str())));
                }
                else
                {
                    throw std::invalid_argument("Unknown filter type: " + type);
                }
            }
            tc->AddFilter(group);
        }
    }

} // namespace ns3