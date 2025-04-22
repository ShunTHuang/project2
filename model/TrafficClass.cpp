//
// Created by shun on 4/16/25.
//

#include "TrafficClass.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

NS_LOG_COMPONENT_DEFINE("TrafficClass");

TrafficClass::TrafficClass(uint32_t maxPkts, double w, uint32_t prio, bool isDef, uint32_t quantum)
    : packets(0),
      maxPackets(maxPkts),
      weight(w),
      quantum(quantum),
      priority_level(prio),
      isDefault(isDef),
      counts(0)
{
}

bool
TrafficClass::Enqueue(Ptr<Packet> p)
{
    if (packets >= maxPackets)
    {
        NS_LOG_WARN("TrafficClass full, dropping packet");
        return false;
    }
    m_queue.push(p);
    ++packets;
    return true;
}

Ptr<Packet>
TrafficClass::Dequeue()
{
    if (m_queue.empty())
        return nullptr;

    auto pkt = m_queue.front();
    NS_ASSERT_MSG(pkt != nullptr, "[Traffic] Dequeue got nullptr from front");
    m_queue.pop();
    --packets;
    return pkt;
}

Ptr<Packet>
TrafficClass::Peek()
{
    if (m_queue.empty())
    {
        NS_LOG_LOGIC("[TrafficClass] Queue empty");
        return nullptr;
    }

    Ptr<Packet> p = m_queue.front();
    NS_ASSERT_MSG(p != nullptr, "[Traffic] Peek got nullptr from queue front");
    return p;
}

bool
TrafficClass::match(Ptr<Packet> p)
{
    if (isDefault && filters.empty())
        return true;

    for (Filter *filter: filters)
    {
        if (filter->match(p))
            return true;
    }
    return false;
}


void
TrafficClass::AddQuantum()
{
    counts += quantum;
}

void
TrafficClass::DecCounts(uint32_t pktSize)
{
    if (counts >= pktSize)
        counts -= pktSize;
    else
    {
        NS_LOG_WARN("Trying to decrease more than available quantum. counts="
                    << counts << ", pktSize=" << pktSize);
        counts = 0;
    }
}

void
TrafficClass::AddFilter(Filter *f)
{
    filters.push_back(f);
}

void
TrafficClass::SetDefault(bool def)
{
    isDefault = def;
}

bool
TrafficClass::IsDefault() const
{
    return isDefault;
}

bool
TrafficClass::IsEmpty() const
{
    return m_queue.empty();
}
