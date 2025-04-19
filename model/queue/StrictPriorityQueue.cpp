//
// Created by peter on 4/16/25.
//
#include "StrictPriorityQueue.h"
#include "TrafficClass.h"
#include <ns3/queue.h>
#include <ns3/packet.h>
#include "ns3/log.h"
#include "ns3/simulator.h"
#include <algorithm>

namespace ns3 {

    NS_LOG_COMPONENT_DEFINE("StrictPriorityQueue");
    NS_OBJECT_ENSURE_REGISTERED(StrictPriorityQueue);

    TypeId
    StrictPriorityQueue::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::StrictPriorityQueue<Packet>")
                .SetParent<Queue<Packet>>()
                .AddConstructor<StrictPriorityQueue>();
        return tid;
    }

    StrictPriorityQueue::StrictPriorityQueue()
    {
        NS_LOG_UNCOND("[StrictPriorityQueue] Constructor: initializing two traffic classes at "
                              << Simulator::Now());
        TrafficClass* tc  = new TrafficClass(100, 1, 1, false);
        TrafficClass* tc2 = new TrafficClass(100, 2, 2, false);
        q_class.push_back(tc);
        q_class.push_back(tc2);
    }

    StrictPriorityQueue::~StrictPriorityQueue()
    {
        NS_LOG_UNCOND("[StrictPriorityQueue] Destructor at " << Simulator::Now());
    }

    Ptr<Packet>
    StrictPriorityQueue::Schedule()
    {
        NS_LOG_UNCOND("[StrictPriorityQueue] Schedule() called at " << Simulator::Now());
        std::vector<TrafficClass*> sorted = q_class;
        std::sort(sorted.begin(), sorted.end(),
                  [](TrafficClass *a, TrafficClass *b) {
                      return a->GetPriority() > b->GetPriority();
                  });
        for (auto cls : sorted)
        {
            NS_LOG_UNCOND("[StrictPriorityQueue] Checking queue priority "
                                  << cls->GetPriority()
                                  << " at time " << Simulator::Now());
            if (!cls->IsEmpty())
            {
                Ptr<Packet> p = cls->Dequeue();
                NS_LOG_UNCOND("[StrictPriorityQueue] Dequeued one packet from priority "
                                      << cls->GetPriority()
                                      << " at time " << Simulator::Now());
                return p;
            }
        }
        NS_LOG_UNCOND("[StrictPriorityQueue] All queues empty, returning nullptr at "
                              << Simulator::Now());
        return nullptr;
    }

    uint32_t
    StrictPriorityQueue::Classify(Ptr<Packet> p)
    {
        NS_LOG_UNCOND("[StrictPriorityQueue] Classify() called, packet uid="
                              << p->GetUid()
                              << ", size=" << p->GetSize()
                              << " at time " << Simulator::Now());
        for (uint32_t i = 0; i < q_class.size(); ++i)
        {
            if (q_class[i]->match(p))
            {
                NS_LOG_UNCOND("[StrictPriorityQueue] Packet uid=" << p->GetUid()
                                                                  << " matched queue " << i
                                                                  << ", priority=" << q_class[i]->GetPriority()
                                                                  << " at time " << Simulator::Now());
                return i;
            }
        }
        return 0;
    }

}