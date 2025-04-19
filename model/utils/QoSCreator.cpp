//
// Created by koichi on 4/18/25.
//

#include "QoSCreator.h"
#include <fstream>

#include "StrictPriorityQueue.h"
#include "DeficitRoundRobin.h"

using json = nlohmann::json;

DiffServ* QoSCreator::createQoS(const std::string& filename) {
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Failed to open config file");

    json config;
    file >> config;

    std::vector<TrafficClass*> trafficClasses;

    for (const auto& queue : config["queues"]) {
        uint32_t priority = queue["priority_level"];
        uint32_t maxPackets = queue["maxPackets"];
        uint32_t quantum = queue["quantum"];
        double weight = queue["weight"];
        bool isDefault = queue["isDefault"];

        auto* tc = new TrafficClass(priority, maxPackets, quantum, weight, isDefault);

        parseFilters(queue["filters"], tc);
    }

    std::string qos_mechanism = config["qos_mechanism"];
    if (qos_mechanism == "spq")
        return new StrictPriorityQueue(trafficClasses);
    if (qos_mechanism == "drr")
        return new DeficitRoundRobin(trafficClasses);

    throw std::invalid_argument("Unknown qos mechanism");
}

void QoSCreator::parseFilters(
    const nlohmann::json& filtersConfig,
    TrafficClass* trafficClass
) {
    for (const auto& filterGroupJson : filtersConfig) {
        auto* group = new Filter();

        for (const auto& filter : filterGroupJson) {
            std::string type = filter["filterType"];

            if (type == "Protocol") {
                std::string proto = filter["filterValue"];
                if (proto == "tcp") {
                    group->AddElement(new Protocol(6));
                } else if (proto == "udp") {
                    group->AddElement(new Protocol(17));
                }
            } else if (type == "DstPort") {
                group->AddElement(new DstPort(filter["filterValue"]));
            } else if (type == "SrcPort") {
                group->AddElement(new SrcPort(filter["filterValue"]));
            } else if (type == "SrcIP") {
                group->AddElement(new SrcIP(ns3::Ipv4Address(filter["filterValue"])));
            } else if (type == "DstIP") {
                group->AddElement(new DstIP(ns3::Ipv4Address(filter["filterValue"])));
            } else if (type == "SrcMask") {
                group->AddElement(new SrcMask(
                    ns3::Ipv4Address(filter["filterValue"]["address"]),
                    ns3::Ipv4Mask(filter["filterValue"]["mask"])
                ));
            } else if (type == "DstMask") {
                group->AddElement(new DstMask(
                    ns3::Ipv4Address(filter["filterValue"]["address"]),
                    ns3::Ipv4Mask(filter["filterValue"]["mask"])
                ));
            } else {
                throw std::invalid_argument("Unknown filter type");
            }
        }
        trafficClass->AddFilter(group);
    }
}




