//
// Created by koichi on 4/17/25.
//

#include "DeficitRoundRobin.h"

namespace ns3 {
    Ptr<Packet> DeficitRoundRobin::Schedule() override {
        TrafficClass* currQueue = q_class[queueIndex];
        currQueue->AddQuantum();
        if (currQueue->Peek()->GetSize() <= currQueue->GetQuantum())
            return currQueue->Dequeue();
        return nullptr;
    }

    uint32_t DeficitRoundRobin::Classify(Ptr<Packet> p) override {
        return 0;
    }
}