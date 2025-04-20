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
        std::vector<uint32_t> m_quantumList;

    public:
        static TypeId GetTypeId();

        DeficitRoundRobin();
        DeficitRoundRobin(const std::vector<uint32_t>& quantumList);
        ~DeficitRoundRobin() override;

        Ptr<Packet> Schedule() override;
        uint32_t Classify(Ptr<Packet> p) override;
    };
}


#endif //DEFICITROUNDROBIN_H
