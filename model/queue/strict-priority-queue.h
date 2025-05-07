/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Peter <shuang85@dons.usfca.edu>
 */

#ifndef SPQQUEUE_H
#define SPQQUEUE_H

#include "diff-serv.h"

namespace ns3
{

/**
 * @brief A DiffServ queue using strict priority scheduling (SPQ).
 *
 * This scheduler always pick the packet from highest priority non-empty class.
 * Lower priority classes will be served only if high one is empty.
 */
    class StrictPriorityQueue : public DiffServ
    {
    public:
        /**
         * @brief Get TypeId for this class in ns-3 system.
         *
         * @return The TypeId of StrictPriorityQueue.
         */
        static TypeId GetTypeId();

        /**
         * @brief Default constructor.
         */
        StrictPriorityQueue();

        /**
         * @brief Constructor with custom traffic class list.
         *
         * @param trafficClasses Predefined list of traffic classes.
         */
        StrictPriorityQueue(std::vector<TrafficClass*> trafficClasses);

        /**
         * @brief Destructor.
         */
        ~StrictPriorityQueue() override;

        /**
         * @brief Called after construction finished.
         *
         * Useful for loading traffic class from config file if needed.
         */
        void NotifyConstructionCompleted() override;

    protected:
        /**
         * @brief Select next packet using strict priority logic.
         *
         * @return Next packet to dequeue or nullptr if all queues empty.
         */
        Ptr<Packet> Schedule() override;

        /**
         * @brief Classify packet into correct traffic class index.
         *
         * @param packet The packet to classify.
         * @return Index of traffic class that matched.
         */
        uint32_t Classify(Ptr<Packet> packet) override;

    private:
        std::string m_configFile; ///< Optional config file path for loading classes.
    };

} // namespace ns3

#endif // SPQQUEUE_H
