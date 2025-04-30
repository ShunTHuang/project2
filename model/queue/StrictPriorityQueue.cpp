//
// Created by peter on 4/16/25.
//
#include "StrictPriorityQueue.h"
#include "TrafficClass.h"
#include <ns3/queue.h>
#include <ns3/packet.h>
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/uinteger.h"
#include "utils/QoSCreator.h"


namespace ns3 {

    NS_LOG_COMPONENT_DEFINE("StrictPriorityQueue");
    NS_OBJECT_ENSURE_REGISTERED(StrictPriorityQueue);

    TypeId
    StrictPriorityQueue::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::StrictPriorityQueue")
          .SetParent<Queue<Packet>>()
          .AddConstructor<StrictPriorityQueue>()
          .AddAttribute("ConfigFile",
                        "Path to JSON file describing traffic classes",
                        StringValue(""),
                        MakeStringAccessor(&StrictPriorityQueue::m_configFile),
                        MakeStringChecker());
        return tid;
    }

    StrictPriorityQueue::StrictPriorityQueue() = default;

    StrictPriorityQueue::StrictPriorityQueue(std::vector<TrafficClass*> trafficClasses)
    {
        m_classes = std::move(trafficClasses);
    }

    StrictPriorityQueue::~StrictPriorityQueue()
    {
        for (auto* cls : m_classes)
        {
            delete cls;
        }
        m_classes.clear();
    }

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

}