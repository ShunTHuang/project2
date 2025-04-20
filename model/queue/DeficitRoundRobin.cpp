//
// Created by koichi on 4/17/25.
//
#include "DeficitRoundRobin.h"
#include "TrafficClass.h"
#include "ns3/log.h"
#include "ns3/simulator.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("DeficitRoundRobin");
    NS_OBJECT_ENSURE_REGISTERED(DeficitRoundRobin);

    TypeId
    DeficitRoundRobin::GetTypeId() {
        static TypeId tid = TypeId("ns3::DeficitRoundRobin<Packet>")
            .SetParent<Queue<Packet>>()
            .AddConstructor<DeficitRoundRobin>();
        return tid;
    }

    DeficitRoundRobin::DeficitRoundRobin()
        : queueIndex(0) {
        NS_LOG_UNCOND("[DeficitRoundRobin] Constructor: initializing three traffic classes at " << Simulator::Now());
        m_quantumList = {300, 200, 100}; //default
        for (size_t i = 0; i < m_quantumList.size(); ++i) {
            auto* tc = new TrafficClass(100, 0, 0, false);
            if (!tc) {
                std::cout << "tc new failed at index " << i << std::endl;
            }
            q_class.push_back(tc);
        }
    }

    DeficitRoundRobin::DeficitRoundRobin(const std::vector<uint32_t>& quantumList)
        : queueIndex(0), m_quantumList(quantumList){
        for (size_t i = 0; i < m_quantumList.size(); ++i) {
            auto* tc = new TrafficClass(100, 0, 0, false);
            if (!tc) {
                std::cout << "tc new failed at index " << i << std::endl;
            }
            q_class.push_back(tc);
        }
    }

    DeficitRoundRobin::~DeficitRoundRobin() {
        NS_LOG_UNCOND("[DeficitRoundRobin] Destructor at " << Simulator::Now());
    }

    Ptr<Packet> DeficitRoundRobin::Schedule() {
        NS_LOG_UNCOND("[DeficitRoundRobin] Schedule running at " << Simulator::Now());
        uint32_t attempts = q_class.size();
        while (attempts--) {
            TrafficClass* currQueue = q_class[queueIndex];

            if (!currQueue->IsEmpty()) {
                currQueue->AddQuantum(m_quantumList[queueIndex]);

                Ptr<Packet> pkt = currQueue->Peek();
                if (pkt && pkt->GetSize() <= currQueue->GetQuantum()) {
                    queueIndex = (queueIndex + 1) % q_class.size();
                    return currQueue->Dequeue();
                }
            }
            queueIndex = (queueIndex + 1) % q_class.size();
        }
        return nullptr;
    }

    uint32_t DeficitRoundRobin::Classify(ns3::Ptr<ns3::Packet> p) {
        NS_LOG_UNCOND("[DeficitRoundRobin] Classify running at " << Simulator::Now());
        static uint32_t counter = 0;
        return counter++ % q_class.size();
    }
}