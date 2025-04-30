//
// Created by koichi on 4/17/25.
//

#ifndef DEFICITROUNDROBIN_H
#define DEFICITROUNDROBIN_H

#include "DiffServ.h"

namespace ns3 {
    class DeficitRoundRobin : public DiffServ
    {
    public:
        static TypeId GetTypeId();

        DeficitRoundRobin();
        explicit DeficitRoundRobin(std::vector<TrafficClass*> trafficClasses);
        ~DeficitRoundRobin() override;

        void DoInitialize() override;

        Ptr<Packet> Schedule() override;
        uint32_t Classify(Ptr<Packet> packet) override;

    private:
        uint32_t m_queueIndex;
        std::string m_configFile;
    };
}


#endif //DEFICITROUNDROBIN_H
