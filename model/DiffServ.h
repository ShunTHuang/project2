//
// Created by shun on 4/16/25.
//

#ifndef DIFFSERV_H
#define DIFFSERV_H

#include <vector>
#include "TrafficClass.h"
#include "ns3/queue.h"

namespace ns3 {

    class DiffServ : public Queue<Packet>
    {
    public:
        virtual ~DiffServ();

        bool Enqueue(Ptr<Packet> packet);
        Ptr<Packet> Dequeue();
        Ptr<Packet> Remove();
        Ptr<const Packet> Peek() const;

        static TypeId GetTypeId();

        virtual Ptr<Packet> Schedule() = 0;
        virtual uint32_t Classify(Ptr<Packet> packet) = 0;

    protected:
        std::vector<TrafficClass*> m_classes;
    };

} // namespace ns3
#endif //DIFFSERV_H