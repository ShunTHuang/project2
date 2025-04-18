//
// Created by koichi on 4/17/25.
//

#ifndef DEFICITROUNDROBIN_H
#define DEFICITROUNDROBIN_H

#include "DiffServ.h"

namespace ns3 {

    class DeficitRoundRobin : public DiffServ {
    private:
        uint32_t queueIndex;
        const uint32_t quantum;

    public:
        static TypeId GetTypeId();

        DeficitRoundRobin();
        DeficitRoundRobin(uint32_t quantum);
        ~DeficitRoundRobin() override;

        Ptr<Packet> Schedule() override;
        uint32_t Classify(Ptr<Packet> p) override;
    };
}


#endif //DEFICITROUNDROBIN_H
