//
// Created by shun on 4/16/25.
//

#ifndef DIFFSERV_H
#define DIFFSERV_H

#include <vector>
#include <mutex>
#include "ns3/ptr.h"
#include "ns3/packet.h"
#include "TrafficClass.h"

namespace ns3 {
    class DiffServ : public ns3::Object {
    protected:
        std::vector<TrafficClass*> q_class;
        mutable std::mutex queue_mutex;

    public:
        virtual ~DiffServ();

        bool Enqueue(ns3::Ptr<ns3::Packet> p);
        ns3::Ptr<ns3::Packet> Dequeue();
        ns3::Ptr<ns3::Packet> Remove();
        ns3::Ptr<const ns3::Packet> Peek() const;

        static ns3::TypeId GetTypeId();
        virtual ns3::Ptr<ns3::Packet> Schedule() = 0;
        virtual uint32_t Classify(ns3::Ptr<ns3::Packet> p) = 0;
    };
}

#endif //DIFFSERV_H
