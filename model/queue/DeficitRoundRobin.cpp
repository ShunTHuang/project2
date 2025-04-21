//
// Created by koichi on 4/17/25.
//
#include "DeficitRoundRobin.h"
#include "TrafficClass.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "utils/QoSCreator.h"

namespace ns3 {
    NS_LOG_COMPONENT_DEFINE("DeficitRoundRobin");
    NS_OBJECT_ENSURE_REGISTERED(DeficitRoundRobin);

    TypeId
    DeficitRoundRobin::GetTypeId() {
        static TypeId tid = TypeId("ns3::DeficitRoundRobin<Packet>")
            .SetParent<Queue<Packet>>()
            .AddConstructor<DeficitRoundRobin>()
            .AddAttribute("ConfigFile",
                              "Path to JSON file describing traffic classes",
                              StringValue(""),
                              MakeStringAccessor(&DeficitRoundRobin::m_configFile),
                              MakeStringChecker());
        return tid;
    }

    DeficitRoundRobin::DeficitRoundRobin()
        : queueIndex(0) {
        NS_LOG_UNCOND("[DeficitRoundRobin] Constructor: initializing three traffic classes at " << Simulator::Now());
        std::vector<uint32_t> m_quantumList = {300, 200, 100}; //default
        for (size_t i = 0; i < m_quantumList.size(); ++i) {
            auto* tc = new TrafficClass(100, 0, 0, false, m_quantumList[i]);
            q_class.push_back(tc);
        }
    }

    void
    DeficitRoundRobin::DoInitialize()
    {
        Queue<Packet>::DoInitialize();
        if (!m_configFile.empty()) {
            QoSCreator maker;
            std::vector<TrafficClass*> trafficClasses = maker.createTrafficClasses (m_configFile);
            q_class.swap (trafficClasses);
            NS_LOG_UNCOND ("Loaded " << q_class.size () << " traffic classes from " << m_configFile);
        }
    }

    DeficitRoundRobin::DeficitRoundRobin(std::vector<TrafficClass*> trafficClasses)
        : queueIndex(0) {
        q_class.swap (trafficClasses);
    }

    DeficitRoundRobin::~DeficitRoundRobin() {
        NS_LOG_UNCOND("[DeficitRoundRobin] Destructor at " << Simulator::Now());
    }

    Ptr<Packet> DeficitRoundRobin::Schedule() {
        NS_LOG_UNCOND("[DeficitRoundRobin] Schedule running at " << Simulator::Now());
        uint32_t attempts = q_class.size();
        while (attempts--) {
            if (TrafficClass* currQueue = q_class[queueIndex]; currQueue) {
                currQueue->AddQuantum();
                NS_LOG_UNCOND("[DeficitRoundRobin] AddQuantum running at " << Simulator::Now());
                if (Ptr<Packet> pkt = currQueue->Peek();pkt && pkt->GetSize() <= currQueue->GetCounts()) {
                    NS_LOG_UNCOND("[DeficitRoundRobin] DecCounts running at " << Simulator::Now());
                    queueIndex = (queueIndex + 1) % q_class.size();
                    currQueue->DecCounts(pkt->GetSize());
                    return currQueue->Dequeue();
                }
            }
            queueIndex = (queueIndex + 1) % q_class.size();
        }
        return nullptr;
    }

    uint32_t DeficitRoundRobin::Classify(Ptr<Packet> p) {
        NS_LOG_UNCOND("[DeficitRoundRobin] Classify running at " << Simulator::Now());

        for (uint32_t i = 0; i < q_class.size(); ++i) {
            if (q_class[i] && q_class[i]->match(p)) {
                NS_LOG_UNCOND("Matched class index = " << i);
                return i;
            }
        }

        for (uint32_t i = 0; i < q_class.size(); ++i) {
            if (q_class[i] && q_class[i]->IsDefault()) {
                NS_LOG_UNCOND("Matched class index = " << i);
                return i;
            }
        }

        return 0;
    }
}