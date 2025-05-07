/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Koichi <knakata@dons.usfca.edu>
 */

#include "qos-creator.h"
#include <fstream>
#include <stdexcept>

#include "filter_elements/destination-ip-address.h"
#include "filter_elements/destination-mask.h"
#include "filter_elements/destination-port-number.h"
#include "filter_elements/protocol-number.h"
#include "filter_elements/source-ip-address.h"
#include "filter_elements/source-mask.h"
#include "filter_elements/source-port-number.h"
#include "queue/strict-priority-queue.h"
#include "queue/deficit-round-robin.h"

namespace ns3
{

/**
 * @brief Parse config file and create list of traffic classes.
 *
 * @param filename Path to JSON config file.
 * @return Vector of pointer to created TrafficClass.
 */
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

/**
 * @brief Create a QoS object (DiffServ) from config file.
 *
 * @param filename Path to JSON config file.
 * @return A pointer to created DiffServ-based queue.
 */
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

/**
 * @brief Helper to parse filters section inside traffic class config.
 *
 * @param filtersConfig JSON object with filter data.
 * @param tc Pointer to traffic class to add filters into.
 */
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
                    group->AddElement(new ProtocolNumber(protoNumber));
                }
                else if (type == "DstPort")
                {
                    group->AddElement(new DestinationPortNumber(f["filterValue"]));
                }
                else if (type == "SrcPort")
                {
                    group->AddElement(new SourcePortNumber(f["filterValue"]));
                }
                else if (type == "SrcIP")
                {
                    group->AddElement(new SourceIPAddress(Ipv4Address(f["filterValue"].get<std::string>().c_str())));
                }
                else if (type == "DstIP")
                {
                    group->AddElement(new DestinationIPAddress(Ipv4Address(f["filterValue"].get<std::string>().c_str())));
                }
                else if (type == "SrcMask")
                {
                    std::string addr = f["filterValue"]["address"];
                    std::string mask = f["filterValue"]["mask"];
                    group->AddElement(new SourceMask(Ipv4Address(addr.c_str()), Ipv4Mask(mask.c_str())));
                }
                else if (type == "DstMask")
                {
                    std::string addr = f["filterValue"]["address"];
                    std::string mask = f["filterValue"]["mask"];
                    group->AddElement(new DestinationMask(Ipv4Address(addr.c_str()), Ipv4Mask(mask.c_str())));
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
