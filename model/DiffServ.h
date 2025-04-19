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
    class DiffServ {
    protected:
        std::vector<TrafficClass*> q_class;
	    mutable std::mutex queue_mutex;

    public:
        DiffServ(std::vector<TrafficClass*>& q_class);
        virtual ~DiffServ();

        bool Enqueue(Ptr<Packet> p);
        Ptr<Packet> Dequeue();
        Ptr<Packet> Remove();
        Ptr<const Packet> Peek() const;

        virtual Ptr<Packet> Schedule() = 0;
        virtual uint32_t Classify(Ptr<Packet> p) = 0;
    };
}



#endif //DIFFSERV_H
