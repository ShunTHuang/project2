//
// Created by shun on 4/16/25.
//

#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include <queue>
#include <vector>
#include "ns3/packet.h"
#include "ns3/ptr.h"
#include "filter.h"

class TrafficClass {
private:
    uint32_t packets;
    uint32_t maxPackets;
    double weight;
    uint32_t priority_level;
    bool isDefault;

    std::queue<ns3::Ptr<ns3::Packet>> m_queue;
    std::vector<Filter> filters;

public:
    TrafficClass(uint32_t maxPkts, double w, uint32_t prio, bool isDef = false);

    bool Enqueue(ns3::Ptr<ns3::Packet> p);
    ns3::Ptr<ns3::Packet> Dequeue();
    bool match(ns3::Ptr<ns3::Packet> p);

    void AddFilter(const Filter& f);
    void SetDefault(bool def);
    bool IsDefault() const;
};



#endif //TRAFFICCLASS_H
