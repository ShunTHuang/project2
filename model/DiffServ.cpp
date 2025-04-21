//
// Created by shun on 4/16/25.
//

#include "DiffServ.h"

namespace ns3 {
    DiffServ::~DiffServ() {
        for (auto tc : q_class) {
            delete tc;
        }
    }

    TypeId DiffServ::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::DiffServ<Packet>")
                .SetParent<Queue>()
            .SetGroupName("Network");
        return tid;
    }

    bool DiffServ::Enqueue(Ptr<Packet> p) {
        uint32_t index = Classify(p); // Classify() returns the index of the queue
        NS_LOG_UNCOND("Enqueue packet UID=" << p->GetUid() << " to class " << index);
        if (index >= q_class.size()) {
            return false;
        }
        return q_class[index]->Enqueue(p);
    }

    Ptr<Packet> DiffServ::Dequeue() {
        return Schedule();
    }

    Ptr<Packet> DiffServ::Remove() {
        return Schedule();
    }

    Ptr<const Packet> DiffServ::Peek() const {
        for (const auto& tc : q_class) {
            Ptr<const Packet> p = tc->Peek();
            if (p != nullptr) {
                return p;
            }
        }
        return nullptr;
    }
}