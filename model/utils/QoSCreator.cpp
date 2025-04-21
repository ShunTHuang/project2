//
// Created by koichi on 4/18/25.
//

#include "QoSCreator.h"
#include <fstream>
#include <stdexcept>
#include "filter_elements/protocol.h"
#include "filter_elements/dst_port.h"
#include "filter_elements/src_port.h"
#include "filter_elements/src_ip.h"
#include "filter_elements/dst_ip.h"
#include "filter_elements/src_mask.h"
#include "filter_elements/dst_mask.h"
#include "queue/StrictPriorityQueue.h"
#include "queue/DeficitRoundRobin.h"

std::vector<TrafficClass*>
QoSCreator::createTrafficClasses(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open config file: " + filename);
    }
    json config;
    file >> config;

    std::vector<TrafficClass*> classes;
    for (const auto& q : config["queues"]) {
        uint32_t priority   = q["priority_level"];
        uint32_t maxPackets = q["maxPackets"];
        double   weight     = q["weight"];
        uint32_t quantum = q["quantum"];
        bool     isDefault  = q["isDefault"];

        TrafficClass* tc = new TrafficClass(maxPackets, weight, priority , isDefault, quantum);

        parseFilters(q["filters"], tc);

        classes.push_back(tc);
    }
    return classes;
}

DiffServ*
QoSCreator::createQoS(const std::string& filename) {
    auto classes = createTrafficClasses(filename);

    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open config file: " + filename);
    }
    json config;
    file >> config;
    std::string mech = config["qos_mechanism"];

    if (mech == "spq") {
        return new StrictPriorityQueue(classes);
    }
    if (mech == "drr") {
        return new DeficitRoundRobin(classes);
    }
    throw std::invalid_argument("Unknown qos mechanism: " + mech);
}

void
QoSCreator::parseFilters(const json& filtersConfig, TrafficClass* tc) {
    for (const auto& groupJson : filtersConfig) {
        Filter* group = new Filter();
        for (const auto& f : groupJson) {
            std::string type = f["filterType"];
            if (type == "Protocol") {
                std::string p = f["filterValue"];
                group->AddElement(p == "tcp"
                                  ? static_cast<FilterElement*>(new Protocol(6))
                                  : static_cast<FilterElement*>(new Protocol(17)));
            }
            else if (type == "DstPort") {
                group->AddElement(new DstPort(f["filterValue"]));
            }
            else if (type == "SrcPort") {
                group->AddElement(new SrcPort(f["filterValue"]));
            }
            else if (type == "SrcIP") {
                group->AddElement(new SrcIP(Ipv4Address(f["filterValue"])));
            }
            else if (type == "DstIP") {
                group->AddElement(new DstIP(Ipv4Address(f["filterValue"])));
            }
            else if (type == "SrcMask") {
                auto addr = f["filterValue"]["address"];
                auto mask = f["filterValue"]["mask"];
                group->AddElement(new SrcMask(Ipv4Address(addr), Ipv4Mask(mask)));
            }
            else if (type == "DstMask") {
                auto addr = f["filterValue"]["address"];
                auto mask = f["filterValue"]["mask"];
                group->AddElement(new DstMask(Ipv4Address(addr), Ipv4Mask(mask)));
            }
            else {
                throw std::invalid_argument("Unknown filter type: " + type);
            }
        }
        tc->AddFilter(group);
    }
}