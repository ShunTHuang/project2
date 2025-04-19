//
// Created by koichi on 4/17/25.
//

#include "DeficitRoundRobin.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("DeficitRoundRobin");
    NS_OBJECT_ENSURE_REGISTERED(DeficitRoundRobin);

    TypeId
    DeficitRoundRobin::GetTypeId() {
        static TypeId tid = TypeId("ns3::SpqQueue")
                .SetParent<DiffServ>()
                .AddConstructor<DeficitRoundRobin>();
        return tid;
    }

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