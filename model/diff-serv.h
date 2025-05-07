/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef DIFFSERV_H
#define DIFFSERV_H

#include <vector>
#include "traffic-class.h"
#include "ns3/queue.h"

namespace ns3
{

/**
 * @brief Abstract base class for Differentiated Services (DiffServ) queueing.
 *
 * DiffServ implements differentiated handling of packets by classifying them into
 * traffic classes and scheduling their transmission based on a specific algorithm.
 * This class is designed to be subclassed with specific scheduling policies (e.g., SPQ, DRR).
 */
    class DiffServ : public Queue<Packet>
    {
    public:
        /**
         * Virtual destructor.
         */
        virtual ~DiffServ();

        /**
         * Enqueue a packet into the appropriate traffic class.
         *
         * @param packet The packet to enqueue.
         * @return True if the packet was successfully enqueued.
         */
        bool Enqueue(Ptr<Packet> packet);

        /**
         * Dequeue the next packet according to the scheduling algorithm.
         *
         * @return The dequeued packet, or null if the queue is empty.
         */
        Ptr<Packet> Dequeue();

        /**
         * Remove and return the next packet without applying scheduling logic.
         *
         * @return The removed packet, or null if the queue is empty.
         */
        Ptr<Packet> Remove();

        /**
         * Peek at the next packet without removing it from the queue.
         *
         * @return A const pointer to the next packet, or null if the queue is empty.
         */
        Ptr<const Packet> Peek() const;

        /**
         * Get the ns-3 TypeId for this class.
         *
         * @return The TypeId.
         */
        static TypeId GetTypeId();

        /**
         * Pure virtual method to define scheduling behavior.
         *
         * @return The next scheduled packet to be dequeued.
         */
        virtual Ptr<Packet> Schedule() = 0;

        /**
         * Pure virtual method to classify a packet into a traffic class.
         *
         * @param packet The packet to classify.
         * @return The index of the corresponding traffic class.
         */
        virtual uint32_t Classify(Ptr<Packet> packet) = 0;

    protected:
        std::vector<TrafficClass*> m_classes; ///< List of traffic classes used by the scheduler.
    };

} // namespace ns3

#endif //DIFFSERV_H