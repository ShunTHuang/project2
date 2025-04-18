//
// Created by koichi on 4/17/25.
//

#include "DeficitRoundRobin.h"

DeficitRoundRobin::DeficitRoundRobin(const uint32_t quantum)
    : queueIndex(0), quantum(quantum) {}

ns3::Ptr<ns3::Packet> DeficitRoundRobin::Schedule() override {
    TrafficClass* currQueue = q_class[queueIndex];
    currQueue->AddQuantum(quantum);
    if (currQueue->peek()->GetSize() <= currQueue->GetQuantum())
        currQueue->Dequeue();
}

uint32_t DeficitRoundRobin::Classify(ns3::Ptr<ns3::Packet> p) override {

}