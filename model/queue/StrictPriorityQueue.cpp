/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Peter <shuang85@dons.usfca.edu>
 */

#include "StrictPriorityQueue.h"
#include "TrafficClass.h"
#include <ns3/queue.h>
#include <ns3/packet.h>
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/uinteger.h"
#include "utils/QoSCreator.h"

namespace ns3
{

    NS_LOG_COMPONENT_DEFINE("StrictPriorityQueue");
    NS_OBJECT_ENSURE_REGISTERED(StrictPriorityQueue);

/**
 * @brief Get TypeId for this class in ns-3 system.
 *
 * @return The TypeId of StrictPriorityQueue.
 */
    TypeId
    StrictPriorityQueue::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::StrictPriorityQueue<Packet>")
                                    .SetParent<Queue<Packet>>()
                .AddConstructor<StrictPriorityQueue>()
                .AddAttribute("ConfigFile",
                              "Path to JSON file describing traffic classes",
                              StringValue(""),
                              MakeStringAccessor(&StrictPriorityQueue::m_configFile),
                              MakeStringChecker());
        return tid;
    }

/**
 * @brief Default constructor.
 */
    StrictPriorityQueue::StrictPriorityQueue() = default;

/**
 * @brief Constructor with custom traffic class list.
 *
 * @param trafficClasses Predefined list of traffic classes.
 */
    StrictPriorityQueue::StrictPriorityQueue(std::vector<TrafficClass*> trafficClasses)
    {
        m_classes = std::move(trafficClasses);
    }

/**
 * @brief Destructor.
 */
    StrictPriorityQueue::~StrictPriorityQueue()
    {
        for (auto* cls : m_classes)
        {
            delete cls;
        }
        m_classes.clear();
    }

/**
 * @brief Called after construction finished.
 *
 * Useful for loading traffic class from config file if needed.
 */
    void
    StrictPriorityQueue::NotifyConstructionCompleted()
    {
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

        DiffServ::NotifyConstructionCompleted();
    }

/**
 * @brief Select next packet using strict priority logic.
 *
 * @return Next packet to dequeue or nullptr if all queues empty.
 */
    Ptr<Packet>
    StrictPriorityQueue::Schedule()
    {
        std::vector<TrafficClass*> sorted = m_classes;
        std::sort(sorted.begin(), sorted.end(),
                  [](TrafficClass* a, TrafficClass* b) {
                      return a->GetPriority() < b->GetPriority();
                  });

        for (TrafficClass* cls : sorted)
        {
            if (!cls->IsEmpty())
            {
                return cls->Dequeue();
            }
        }
        return nullptr;
    }

/**
 * @brief Classify packet into correct traffic class index.
 *
 * @param packet The packet to classify.
 * @return Index of traffic class that matched.
 */
    uint32_t
    StrictPriorityQueue::Classify(Ptr<Packet> packet)
    {
        for (uint32_t i = 0; i < m_classes.size(); ++i)
        {
            if (m_classes[i] && m_classes[i]->Match(packet))
            {
                return i;
            }
        }
        return 0;
    }

} // namespace ns3
