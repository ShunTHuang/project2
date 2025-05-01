//
// Created by shun on 4/16/25.
//

#include "Filter.h"

namespace ns3
{

    bool
    Filter::Match(Ptr<Packet> packet)
    {
        for (auto elem : m_elements)
        {
            if (!elem->Match(packet))
            {
                return false;
            }
        }
        return true;
    }

    void
    Filter::AddElement(FilterElement* element)
    {
        m_elements.push_back(element);
    }

} // namespace ns3