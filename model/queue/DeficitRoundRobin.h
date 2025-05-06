/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Koichi <knakata@dons.usfca.edu>
 */

#ifndef DEFICITROUNDROBIN_H
#define DEFICITROUNDROBIN_H

#include "DiffServ.h"

namespace ns3
{

/**
 * @brief Implementation of Deficit Round Robin (DRR) scheduler.
 *
 * DRR try to serve multiple traffic class fairly by using quantum-based round robin.
 * Each class get chance to send based on how much deficit counter it has.
 */
    class DeficitRoundRobin : public DiffServ
    {
    public:
        /**
         * @brief Get TypeId for ns-3 runtime type system.
         *
         * @return The TypeId of this class.
         */
        static TypeId GetTypeId();

        /**
         * @brief Default constructor.
         */
        DeficitRoundRobin();

        /**
         * @brief Constructor that take predefined traffic class list.
         *
         * @param trafficClasses List of traffic class to be used.
         */
        explicit DeficitRoundRobin(std::vector<TrafficClass*> trafficClasses);

        /**
         * @brief Destructor.
         */
        ~DeficitRoundRobin() override;

        /**
         * @brief Initialize method called by simulator.
         */
        void DoInitialize() override;

        /**
         * @brief Schedule next packet to be dequeued using DRR logic.
         *
         * It rotate queue and pick class that has enough deficit count.
         *
         * @return The packet selected to be dequeued, or nullptr.
         */
        Ptr<Packet> Schedule() override;

        /**
         * @brief Classify packet to correct traffic class index.
         *
         * @param packet Packet to be checked.
         * @return Index of traffic class.
         */
        uint32_t Classify(Ptr<Packet> packet) override;

    private:
        uint32_t m_queueIndex;   ///< Current index in round robin.
        std::string m_configFile; ///< Path of optional config file.
    };

} // namespace ns3

#endif //DEFICITROUNDROBIN_H
