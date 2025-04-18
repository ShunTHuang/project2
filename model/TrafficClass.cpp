//
// Created by shun on 4/16/25.
//

#include "TrafficClass.h"
#include "log.h"

NS_LOG_COMPONENT_DEFINE("TrafficClass");


TrafficClass::TrafficClass(uint32_t maxPkts, double w, uint32_t prio, bool isDef)
    : packets(0),
      maxPackets(maxPkts),
      weight(w),
      priority_level(prio),
      isDefault(isDef) {
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

ns3::Ptr<const ns3::Packet> TrafficClass::Peek() const {
    if (!m_queue.empty()) {
        return m_queue.front();
    }
    return nullptr;
}

bool TrafficClass::match(ns3::Ptr<ns3::Packet> p) {
    if (isDefault && filters.empty()) {
        return true;
    }
    for (const auto &f: filters) {
        //TODO: fix this const problem
        if (f.match(p)) {
            return true;
        }
    }
    return false;
}

void TrafficClass::AddFilter(const Filter &f) {
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
