//
// Created by koichi on 4/17/25.
//

#include "DeficitRoundRobin.h"

namespace ns3 {
    ns3::Ptr<ns3::Packet> DeficitRoundRobin::Schedule() override {
        TrafficClass* currQueue = q_class[queueIndex];
        currQueue->AddQuantum();
        if (currQueue->Peek()->GetSize() <= currQueue->GetQuantum())
            return currQueue->Dequeue();
    }

    uint32_t DeficitRoundRobin::Classify(ns3::Ptr<ns3::Packet> p) override {
        return 0;
    }
}