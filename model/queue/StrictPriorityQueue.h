//
// Created by peter on 4/16/25.
//

#ifndef SPQQUEUE_H
#define SPQQUEUE_H

#include "DiffServ.h"

namespace ns3
{

    class StrictPriorityQueue : public DiffServ
    {
    public:
        static TypeId GetTypeId();

        StrictPriorityQueue();
        StrictPriorityQueue(std::vector<TrafficClass*> trafficClasses);
        ~StrictPriorityQueue() override;

        void NotifyConstructionCompleted() override;

    protected:
        Ptr<Packet> Schedule() override;
        uint32_t Classify(Ptr<Packet> packet) override;

    private:
        std::string m_configFile;
    };

} // namespace ns3

#endif