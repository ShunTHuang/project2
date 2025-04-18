//
// Created by peter on 4/16/25.
//
#include "StrictPriorityQueue.h"
#include "TrafficClass.h"
#include <algorithm>
#include "ns3/log.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("StrictPriorityQueue");
    NS_OBJECT_ENSURE_REGISTERED(StrictPriorityQueue);

    TypeId
    StrictPriorityQueue::GetTypeId() {
        static TypeId tid = TypeId("ns3::SpqQueue")
                .SetParent<DiffServ>()
                .AddConstructor<StrictPriorityQueue>();
        return tid;
    }

    StrictPriorityQueue::~StrictPriorityQueue() {
    }

    Ptr<Packet>
    StrictPriorityQueue::Schedule() {
        std::vector<TrafficClass *> sorted = q_class;
        std::sort(sorted.begin(), sorted.end(), [](TrafficClass *a, TrafficClass *b) {
            return a->GetPriority() > b->GetPriority();
        });
        for (auto cls: sorted) {
            if (!cls->IsEmpty()) {
                return cls->Dequeue();
            }
        }
        return nullptr;
    }

    uint32_t Classify(ns3::Ptr<ns3::Packet> p) { return 0; };
}
