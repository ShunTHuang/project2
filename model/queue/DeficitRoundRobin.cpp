/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Koichi <knakata@dons.usfca.edu>
 */

#include "DeficitRoundRobin.h"
#include "TrafficClass.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "utils/QoSCreator.h"

namespace ns3
{

    NS_LOG_COMPONENT_DEFINE("DeficitRoundRobin");
    NS_OBJECT_ENSURE_REGISTERED(DeficitRoundRobin);

/**
 * @brief Get TypeId for ns-3 runtime type system.
 *
 * @return The TypeId of this class.
 */
    TypeId
    DeficitRoundRobin::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::DeficitRoundRobin")
                                    .SetParent<Queue<Packet>>()
                .AddConstructor<DeficitRoundRobin>()
                .AddAttribute("ConfigFile",
                              "Path to JSON file describing traffic classes",
                              StringValue(""),
                              MakeStringAccessor(&DeficitRoundRobin::m_configFile),
                              MakeStringChecker());
        return tid;
    }

/**
 * @brief Default constructor.
 */
    DeficitRoundRobin::DeficitRoundRobin()
            : m_queueIndex(0)
    {
        static const std::vector<uint32_t> defaultQuantum = {300, 200, 100};
        for (uint32_t q : defaultQuantum)
        {
            m_classes.push_back(new TrafficClass(100, 0.0, 0, false, q));
        }
    }

/**
 * @brief Constructor that take predefined traffic class list.
 *
 * @param trafficClasses List of traffic class to be used.
 */
    DeficitRoundRobin::DeficitRoundRobin(std::vector<TrafficClass*> trafficClasses)
            : m_queueIndex(0)
    {
        m_classes.swap(trafficClasses);
    }

/**
 * @brief Destructor.
 */
    DeficitRoundRobin::~DeficitRoundRobin()
    {
        for (auto* cls : m_classes)
        {
            delete cls;
        }
        m_classes.clear();
    }

/**
 * @brief Initialize method called by simulator.
 */
    void
    DeficitRoundRobin::DoInitialize()
    {
        Queue<Packet>::DoInitialize();

        if (!m_configFile.empty())
        {
            QoSCreator creator;

            for (auto* cls : m_classes)
            {
                delete cls;
            }
            m_classes.clear();

            std::vector<TrafficClass*> fromFile = creator.CreateTrafficClasses(m_configFile);
            m_classes.swap(fromFile);
        }
    }

/**
 * @brief Schedule next packet to be dequeued using DRR logic.
 *
 * It rotate queue and pick class that has enough deficit count.
 *
 * @return The packet selected to be dequeued, or nullptr.
 */
    Ptr<Packet>
    DeficitRoundRobin::Schedule()
    {
        uint32_t attempts = m_classes.size();
        while (attempts--)
        {
            TrafficClass* curr = m_classes[m_queueIndex];
            m_queueIndex = (m_queueIndex + 1) % m_classes.size();

            if (!curr)
                continue;

            curr->AddQuantum();

            Ptr<Packet> pkt = curr->Peek();
            if (pkt && pkt->GetSize() <= curr->GetCounts())
            {
                curr->DecCounts(pkt->GetSize());
                return curr->Dequeue();
            }
        }
        return nullptr;
    }

/**
 * @brief Classify packet to correct traffic class index.
 *
 * @param packet Packet to be checked.
 * @return Index of traffic class.
 */
    uint32_t
    DeficitRoundRobin::Classify(Ptr<Packet> packet)
    {
        for (uint32_t i = 0; i < m_classes.size(); ++i)
        {
            if (m_classes[i] && m_classes[i]->Match(packet))
            {
                return i;
            }
        }

        for (uint32_t i = 0; i < m_classes.size(); ++i)
        {
            if (m_classes[i] && m_classes[i]->IsDefault())
            {
                return i;
            }
        }

        return 0;
    }

} // namespace ns3
