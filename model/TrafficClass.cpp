//
// Created by shun on 4/16/25.
//

#include "TrafficClass.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE("TrafficClass");


TrafficClass::TrafficClass(uint32_t priority_level, uint32_t maxPackets,
                           uint32_t quantum, double weight, bool isDefault) :
        packets(0),
        priority_level(priority_level),
        maxPackets(maxPackets),
        quantum(quantum),
        weight(weight),
        isDefault(isDefault) {
}

bool TrafficClass::Enqueue(ns3::Ptr<ns3::Packet> p) {
    if (packets >= maxPackets) {
        NS_LOG_WARN("TrafficClass full, dropping packet");
        return false;
    }
    m_queue.push(p);
    ++packets;
    return true;
}

ns3::Ptr<ns3::Packet> TrafficClass::Dequeue() {
    if (m_queue.empty()) {
        return nullptr;
    }
    auto pkt = m_queue.front();
    m_queue.pop();
    --packets;
    return pkt;
}

ns3::Ptr<ns3::Packet> TrafficClass::Peek() {
    if (m_queue.empty()) {
        NS_LOG_LOGIC("Queue empty");
        return nullptr;
    }

    ns3::Ptr<ns3::Packet> p = m_queue.front();
    return p;
}

bool TrafficClass::match(ns3::Ptr<ns3::Packet> p) {
    if (isDefault && filters.empty()) {
        return true;
    }
    for (Filter *filter: filters) {
        if (filter->match(p)) {
            return true;
        }
    }
    return false;
}


void TrafficClass::AddQuantum() {
    quantum += quantum;
}

void TrafficClass::AddFilter(Filter *f) {

    filters.push_back(f);
}

void TrafficClass::SetDefault(bool def) {
    isDefault = def;
}

bool TrafficClass::IsDefault() const {
    return isDefault;
}

bool TrafficClass::IsEmpty() const {
    return m_queue.empty();
}
