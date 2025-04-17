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
        StrictPriorityQueue ();
        ~StrictPriorityQueue () override;
    protected:
        virtual Ptr<Packet> Schedule () override;
    };

}
#endif