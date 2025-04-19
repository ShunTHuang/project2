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
                .SetParent<Queue<Packet>>()
            .SetGroupName("Network");
        return tid;
    }

    bool DiffServ::Enqueue(ns3::Ptr<ns3::Packet> p) {
        std::lock_guard<std::mutex> lock(queue_mutex);

        uint32_t index = Classify(p); // Classify() returns the index of the queue
        if (index >= q_class.size()) {
            return false;
        }
        return q_class[index]->Enqueue(p);
    }

    ns3::Ptr<ns3::Packet> DiffServ::Dequeue() {
        std::lock_guard<std::mutex> lock(queue_mutex);

        return Schedule();
    }

    ns3::Ptr<ns3::Packet> DiffServ::Remove() {
        std::lock_guard<std::mutex> lock(queue_mutex);

        return Schedule();
    }

    ns3::Ptr<const ns3::Packet> DiffServ::Peek() const {
        std::lock_guard<std::mutex> lock(queue_mutex);

        for (const auto& tc : q_class) {
            ns3::Ptr<const ns3::Packet> p = tc->Peek();
            if (p != nullptr) {
                return p;
            }
        }
        return nullptr;
    }
}