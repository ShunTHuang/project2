/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef TRAFFICCLASS_H
#define TRAFFICCLASS_H

#include <queue>
#include <vector>
#include "Filter.h"

namespace ns3
{

/**
 * @brief Represents a traffic class used in DiffServ-style scheduling.
 *
 * A traffic class maintains a queue of packets and a set of filters used
 * to classify incoming traffic. It also supports weights, priorities,
 * and DRR-style quantum handling for scheduling algorithms.
 */
    class TrafficClass
    {
    public:
        /**
         * @brief Constructor to initialize a traffic class.
         *
         * @param maxPkts Maximum number of packets the queue can hold.
         * @param weight Scheduling weight used in DRR.
         * @param priority Priority level for SPQ.
         * @param isDefault Indicates if this class should be used as a default.
         * @param quantum Quantum value used for DRR scheduling.
         */
        TrafficClass(uint32_t maxPkts, double weight, uint32_t priority, bool isDefault = false, uint32_t quantum = 0);

        /**
         * @brief Enqueue a packet into this traffic class.
         *
         * @param packet The packet to be enqueued.
         * @return True if successfully enqueued, false if the queue is full.
         */
        bool Enqueue(Ptr<Packet> packet);

        /**
         * @brief Dequeue the next packet in the queue.
         *
         * @return The dequeued packet, or nullptr if the queue is empty.
         */
        Ptr<Packet> Dequeue();

        /**
         * @brief Peek at the next packet without removing it.
         *
         * @return A const pointer to the next packet, or nullptr if empty.
         */
        Ptr<const Packet> Peek() const;

        /**
         * @brief Non-const peek for internal access.
         *
         * @return A pointer to the next packet, or nullptr if empty.
         */
        Ptr<Packet> Peek();

        /**
         * @brief Check if a packet matches any of the class's filters.
         *
         * @param packet The packet to match.
         * @return True if the packet matches, false otherwise.
         */
        bool Match(Ptr<Packet> packet);

        /**
         * @brief Add this class's quantum value to its deficit count.
         */
        void AddQuantum();

        /**
         * @brief Decrement the deficit counter based on packet size.
         *
         * @param pktSize Size of the dequeued packet.
         */
        void DecCounts(uint32_t pktSize);

        /**
         * @brief Add a new filter to the class.
         *
         * @param filter The filter to add.
         */
        void AddFilter(Filter* filter);

        /**
         * @brief Set whether this traffic class is the default class.
         *
         * @param isDefault True if this is the default class.
         */
        void SetDefault(bool isDefault);

        /**
         * @brief Check if this traffic class is the default.
         *
         * @return True if default; false otherwise.
         */
        bool IsDefault() const;

        /**
         * @brief Check if the internal packet queue is empty.
         *
         * @return True if empty; false otherwise.
         */
        bool IsEmpty() const;

        /**
         * @brief Get the priority level of this traffic class.
         *
         * @return Priority level.
         */
        uint32_t GetPriority() const { return m_priorityLevel; }

        /**
         * @brief Get the current deficit counter (used in DRR).
         *
         * @return The count value.
         */
        uint32_t GetCounts() const { return m_counts; }

    private:
        uint32_t m_packetCount;       ///< Current number of packets in the queue.
        uint32_t m_maxPackets;        ///< Maximum allowed packets in the queue.
        double m_weight;              ///< Weight for DRR scheduling.
        uint32_t m_quantum;           ///< Quantum used in DRR.
        uint32_t m_priorityLevel;     ///< Priority level for SPQ.
        bool m_isDefault;             ///< Indicates if this is the default class.

        std::queue<Ptr<Packet>> m_queue; ///< Packet queue for this traffic class.
        std::vector<Filter*> m_filters;  ///< List of filters assigned to this class.

        uint32_t m_counts; ///< Current deficit count for DRR.
    };

} // namespace ns3

#endif // TRAFFICCLASS_H