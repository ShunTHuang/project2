//
// Created by shun on 4/16/25.
//

#include "DiffServ.h"

namespace ns3 {
    DiffServ::DiffServ(std::vector<TrafficClass*>& q_class) : q_class(q_class) {}

    DiffServ::~DiffServ() {
        for (auto tc : q_class) {
            delete tc;
        }
    }

    bool DiffServ::Enqueue(Ptr<Packet> p) {
        std::lock_guard lock(queue_mutex);

        uint32_t index = Classify(p); // Classify() returns the index of the queue
        if (index >= q_class.size()) {
            return false;
        }
        return q_class[index]->Enqueue(p);
    }

    Ptr<Packet> DiffServ::Dequeue() {
        std::lock_guard lock(queue_mutex);

        return Schedule();
    }

    Ptr<Packet> DiffServ::Remove() {
        std::lock_guard lock(queue_mutex);

        return Schedule();
    }

    Ptr<const Packet> DiffServ::Peek() const {
        std::lock_guard lock(queue_mutex);

        for (const auto& tc : q_class) {
            Ptr<const Packet> p = tc->Peek();
            if (p != nullptr) {
                return p;
            }
        }
        return nullptr;
    }
}
