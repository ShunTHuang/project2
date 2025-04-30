//
// Created by shun on 4/16/25.
//

#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include <queue>
#include <vector>
#include "Filter.h"

class TrafficClass
{
public:
    TrafficClass(uint32_t maxPkts, double weight, uint32_t priority, bool isDefault = false, uint32_t quantum = 0);

    bool Enqueue(Ptr<Packet> packet);
    Ptr<Packet> Dequeue();
    Ptr<const Packet> Peek() const;
    Ptr<Packet> Peek();

    bool Match(Ptr<Packet> packet);

    void AddQuantum();
    void DecCounts(uint32_t pktSize);
    void AddFilter(Filter* filter);

    void SetDefault(bool isDefault);
    bool IsDefault() const;
    bool IsEmpty() const;

    uint32_t GetPriority() const { return m_priorityLevel; }
    uint32_t GetCounts() const { return m_counts; }

private:
    uint32_t m_packetCount;
    uint32_t m_maxPackets;
    double m_weight;
    uint32_t m_quantum;
    uint32_t m_priorityLevel;
    bool m_isDefault;

    std::queue<Ptr<Packet>> m_queue;
    std::vector<Filter*> m_filters;

    uint32_t m_counts;
};

#endif