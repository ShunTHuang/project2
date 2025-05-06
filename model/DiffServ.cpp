/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "DiffServ.h"

namespace ns3
{

/**
 * @brief Destructor for DiffServ.
 *
 * Frees memory allocated for all traffic classes.
 */
    DiffServ::~DiffServ()
    {
        for (auto tc : m_classes)
        {
            delete tc;
        }
    }

/**
 * @brief Get the TypeId for DiffServ class.
 *
 * Used by the ns-3 object system for introspection and configuration.
 *
 * @return The TypeId for this class.
 */
    TypeId
    DiffServ::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::DiffServ")
                                    .SetParent<Queue<Packet>>()
                .SetGroupName("Network");
        return tid;
    }

/**
 * @brief Enqueue a packet into the appropriate traffic class.
 *
 * This method classifies the packet and enqueues it into the corresponding traffic class.
 *
 * @param packet The packet to be enqueued.
 * @return True if enqueued successfully, false otherwise.
 */
    bool
    DiffServ::Enqueue(Ptr<Packet> packet)
    {
        uint32_t index = Classify(packet); // Classify returns queue index

        if (index >= m_classes.size())
        {
            return false;
        }

        return m_classes[index]->Enqueue(packet);
    }

/**
 * @brief Dequeue a packet using the selected scheduling algorithm.
 *
 * Calls the subclass-defined Schedule method.
 *
 * @return The dequeued packet, or null if no packet is available.
 */
    Ptr<Packet>
    DiffServ::Dequeue()
    {
        return Schedule();
    }

/**
 * @brief Remove a packet using the same logic as Dequeue.
 *
 * Intended to mirror Remove() behavior from the base class, if different from Dequeue().
 *
 * @return The removed packet.
 */
    Ptr<Packet>
    DiffServ::Remove()
    {
        return Schedule();
    }

/**
 * @brief Peek at the next packet in the queue without removing it.
 *
 * Iterates through traffic classes and returns the first available packet.
 *
 * @return A const pointer to the next packet, or null if none are available.
 */
    Ptr<const Packet>
    DiffServ::Peek() const
    {
        for (const auto& tc : m_classes)
        {
            Ptr<const Packet> packet = tc->Peek();
            if (packet != nullptr)
            {
                return packet;
            }
        }
        return nullptr;
    }

} // namespace ns3