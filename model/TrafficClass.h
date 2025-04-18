//
// Created by shun on 4/16/25.
//

#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include <queue>
#include <vector>
#include "ptr.h"
#include "Filter.h"

class TrafficClass {
private:
    uint32_t packets;
    uint32_t maxPackets;
    double weight;
    uint32_t quantum;
    uint32_t priority_level;
    bool isDefault;
    std::queue<ns3::Ptr<ns3::Packet>> m_queue;
    std::vector<Filter> filters;

public:
    TrafficClass(uint32_t maxPkts, double w, uint32_t prio, bool isDef = false);

    bool Enqueue(ns3::Ptr<ns3::Packet> p);

    ns3::Ptr<ns3::Packet> Dequeue();

    bool match(ns3::Ptr<ns3::Packet> p);

    ns3::Ptr<const ns3::Packet> peek() const {
        if (m_queue.empty()) {
            return nullptr;
        }
        return m_queue.front();
    }

    uint32_t GetPriority() const { return priority_level; }

    uint32_t GetQuantum() const { return quantum; }
    void AddQuantum(uint32_t quantum) { quantum += quantum; }

    void AddFilter(const Filter &f);

    void SetDefault(bool def);

    bool IsDefault() const;

    bool IsEmpty() const;
};

#endif
