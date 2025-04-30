//
// Created by shun on 4/16/25.
//

#include "DiffServ.h"

namespace ns3
{

    DiffServ::~DiffServ()
    {
        for (auto tc : m_classes)
        {
            delete tc;
        }
    }

    TypeId
    DiffServ::GetTypeId()
    {
        static TypeId tid = TypeId("ns3::DiffServ")
          .SetParent<Queue<Packet>>()
          .SetGroupName("Network");
        return tid;
    }

    bool
    DiffServ::Enqueue(Ptr<Packet> packet)
    {
        uint32_t index = Classify(packet); // Classify returns queue index

        if (index >= m_classes.size())
        {
            return false;
        }

        return m_classes[index]->Enqueue(packet);
    }

    Ptr<Packet>
    DiffServ::Dequeue()
    {
        return Schedule();
    }

    Ptr<Packet>
    DiffServ::Remove()
    {
        return Schedule();
    }

    Ptr<const Packet>
    DiffServ::Peek() const
    {
        for (const auto& tc : m_classes)
        {
            Ptr<const Packet> packet = tc->Peek();
            if (packet != nullptr)
            {
                return packet;
            }
        }
        return nullptr;
    }

} // namespace ns3