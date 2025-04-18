//
// Created by peter on 4/16/25.
//

#ifndef SPQQUEUE_H
#define SPQQUEUE_H

#include "DiffServ.h"

namespace ns3 {

    class StrictPriorityQueue : public DiffServ
    {
    public:
        static TypeId GetTypeId ();
        StrictPriorityQueue (std::vector<TrafficClass*>& q_class)
            : DiffServ(q_class) {}

        ~StrictPriorityQueue () override;
    protected:
        virtual Ptr<Packet> Schedule() override;
        virtual uint32_t Classify(ns3::Ptr<ns3::Packet> p) override;
    };

}
#endif