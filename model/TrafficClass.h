//
// Created by shun on 4/16/25.
//

#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include <queue>
#include <vector>
#include "Filter.h"

class TrafficClass {
private:
    uint32_t packets;
    uint32_t maxPackets;
    double weight;
    uint32_t quantum;
    uint32_t priority_level;
    bool isDefault;
    std::queue<Ptr<Packet>> m_queue;
    std::vector<Filter*> filters;
    uint32_t counts;

public:
    TrafficClass(uint32_t maxPkts, double w, uint32_t prio, bool isDef = false, uint32_t quantum = 0);

    bool Enqueue(Ptr<Packet> p);

    Ptr<Packet> Dequeue();

    Ptr<const Packet> Peek() const;

    Ptr<Packet> Peek();

    bool match(Ptr<Packet> p);

    uint32_t GetPriority() const { return priority_level; }

    uint32_t GetCounts() const { return counts; }

    void AddQuantum();

    void DecCounts(uint32_t pktSize);

    void AddFilter(Filter* f);

    void SetDefault(bool def);

    bool IsDefault() const;

    bool IsEmpty() const;
};

#endif
