//
// Created by shun on 4/16/25.
//

#include "TrafficClass.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

TrafficClass::TrafficClass(uint32_t maxPkts, double weight, uint32_t priority, bool isDefault, uint32_t quantum)
  : m_packetCount(0),
    m_maxPackets(maxPkts),
    m_weight(weight),
    m_quantum(quantum),
    m_priorityLevel(priority),
    m_isDefault(isDefault),
    m_counts(0)
{
}

bool
TrafficClass::Enqueue(Ptr<Packet> packet)
{
    if (m_packetCount >= m_maxPackets)
    {
        return false;
    }
    m_queue.push(packet);
    ++m_packetCount;
    return true;
}

Ptr<Packet>
TrafficClass::Dequeue()
{
    if (m_queue.empty())
        return nullptr;

    Ptr<Packet> packet = m_queue.front();
    m_queue.pop();
    --m_packetCount;
    return packet;
}

Ptr<Packet>
TrafficClass::Peek()
{
    if (m_queue.empty())
    {
        return nullptr;
    }

    Ptr<Packet> packet = m_queue.front();
    return packet;
}

bool
TrafficClass::Match(Ptr<Packet> packet)
{
    if (m_isDefault && m_filters.empty())
        return true;

    for (Filter* filter : m_filters)
    {
        if (filter->Match(packet))
            return true;
    }
    return false;
}


void
TrafficClass::AddQuantum()
{
    m_counts += m_quantum;
}

void
TrafficClass::DecCounts(uint32_t pktSize)
{
    if (m_counts >= pktSize)
    {
        m_counts -= pktSize;
    }
    else
    {
        m_counts = 0;
    }
}

void
TrafficClass::AddFilter(Filter* filter)
{
    m_filters.push_back(filter);
}

void
TrafficClass::SetDefault(bool isDefault)
{
    m_isDefault = isDefault;
}

bool
TrafficClass::IsDefault() const
{
    return m_isDefault;
}

bool
TrafficClass::IsEmpty() const
{
    return m_queue.empty();
}