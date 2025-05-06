/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang@dons.usfca.edu>
 */

#include "Filter.h"

namespace ns3
{

    /**
     * @brief Checks if the packet matches all filter elements.
     *
     * Iterates through each FilterElement and calls its Match method.
     * Returns false immediately if any element does not match the packet.
     *
     * @param packet The packet to check against the filter.
     * @return True if the packet matches all elements; false otherwise.
     */
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

    /**
     * @brief Adds a filter element to the filter.
     *
     * The element is appended to the internal list and used in future match checks.
     *
     * @param element Pointer to the filter element to be added.
     */
    void
    Filter::AddElement(FilterElement* element)
    {
        m_elements.push_back(element);
    }

} // namespace ns3
