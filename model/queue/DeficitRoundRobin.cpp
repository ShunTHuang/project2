//
// Created by koichi on 4/17/25.
//
#include "DeficitRoundRobin.h"
#include "TrafficClass.h"
#include <algorithm>
#include "ns3/log.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("DeficitRoundRobin");
    NS_OBJECT_ENSURE_REGISTERED(DeficitRoundRobin);

    TypeId
    DeficitRoundRobin::GetTypeId() {
        static TypeId tid = TypeId("ns3::DrrQueue")
            .SetParent<DiffServ>()
            .AddConstructor<DeficitRoundRobin>();
        return tid;
    }

    DeficitRoundRobin::DeficitRoundRobin()
        : queueIndex(0), quantum(0) {}

    DeficitRoundRobin::DeficitRoundRobin(const uint32_t quantum)
        : queueIndex(0), quantum(quantum) {}

    DeficitRoundRobin::~DeficitRoundRobin() {}

    Ptr<Packet> DeficitRoundRobin::Schedule() {
        TrafficClass* currQueue = q_class[queueIndex];
        currQueue->AddQuantum(quantum);
        if (currQueue->Peek()->GetSize() <= currQueue->GetQuantum())
            return currQueue->Dequeue();
        return nullptr;
    }

    uint32_t DeficitRoundRobin::Classify(ns3::Ptr<ns3::Packet> p) {
        return 0;
    }
}