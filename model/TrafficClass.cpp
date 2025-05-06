/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "TrafficClass.h"
#include "ns3/simulator.h"

namespace ns3
{

    /**
     * @brief Constructor to initialize a traffic class.
     *
     * @param maxPkts Maximum number of packets the queue can hold.
     * @param weight Scheduling weight used in DRR.
     * @param priority Priority level for SPQ.
     * @param isDefault Indicates if this class should be used as a default.
     * @param quantum Quantum value used for DRR scheduling.
     */
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

    /**
     * @brief Enqueue a packet into this traffic class.
     *
     * @param packet The packet to be enqueued.
     * @return True if successfully enqueued, false if the queue is full.
     */
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

    /**
     * @brief Dequeue the next packet in the queue.
     *
     * @return The dequeued packet, or nullptr if the queue is empty.
     */
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

    /**
     * @brief Non-const peek for internal access.
     *
     * @return A pointer to the next packet, or nullptr if empty.
     */
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

    /**
     * @brief Check if a packet matches any of the class's filters.
     *
     * @param packet The packet to match.
     * @return True if the packet matches, false otherwise.
     */
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

    /**
     * @brief Add this class's quantum value to its deficit count.
     */
    void
    TrafficClass::AddQuantum()
    {
        m_counts += m_quantum;
    }

    /**
     * @brief Decrement the deficit counter based on packet size.
     *
     * @param pktSize Size of the dequeued packet.
     */
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

    /**
     * @brief Add a new filter to the class.
     *
     * @param filter The filter to add.
     */
    void
    TrafficClass::AddFilter(Filter* filter)
    {
        m_filters.push_back(filter);
    }

    /**
     * @brief Set whether this traffic class is the default class.
     *
     * @param isDefault True if this is the default class.
     */
    void
    TrafficClass::SetDefault(bool isDefault)
    {
        m_isDefault = isDefault;
    }

    /**
     * @brief Check if this traffic class is the default.
     *
     * @return True if default; false otherwise.
     */
    bool
    TrafficClass::IsDefault() const
    {
        return m_isDefault;
    }

    /**
     * @brief Check if the internal packet queue is empty.
     *
     * @return True if empty; false otherwise.
     */
    bool
    TrafficClass::IsEmpty() const
    {
        return m_queue.empty();
    }

} // namespace ns3
