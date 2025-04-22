//
// Created by shun on 4/16/25.
//

#ifndef DIFFSERV_H
#define DIFFSERV_H

#include <vector>
#include "TrafficClass.h"
#include "ns3/queue.h"

namespace ns3
{
    class DiffServ : public Queue<Packet> {
    protected:
        std::vector<TrafficClass *> q_class;

    public:
        virtual ~DiffServ();

        bool Enqueue(Ptr<Packet> p);

        Ptr<Packet> Dequeue();

        Ptr<Packet> Remove();

        Ptr<const Packet> Peek() const;

        static TypeId GetTypeId();

        virtual Ptr<Packet> Schedule() = 0;

        virtual uint32_t Classify(Ptr<Packet> p) = 0;
    };

}
#endif //DIFFSERV_H
