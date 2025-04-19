//
// Created by koichi on 4/17/25.
//

#ifndef DEFICITROUNDROBIN_H
#define DEFICITROUNDROBIN_H
#include "DiffServ.h"


class DeficitRoundRobin : public DiffServ {
private:
    uint32_t queueIndex = 0;
public:
    DeficitRoundRobin(std::vector<TrafficClass*>& q_class)
    : DiffServ(q_class) {}

    ns3::Ptr<ns3::Packet> Schedule() override;
    uint32_t Classify(ns3::Ptr<ns3::Packet> p) override;
};


#endif //DEFICITROUNDROBIN_H
