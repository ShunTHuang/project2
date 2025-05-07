/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang@dons.usfca.edu>
 */

#ifndef FILTER_H
#define FILTER_H

#include "filter-element.h"

namespace ns3
{

/**
 * @brief Represents a filter composed of multiple filter elements.
 *
 * A Filter is used to match packets against a sequence of FilterElements.
 * Each element defines a matching criterion, and a packet matches the filter
 * only if it satisfies all elements in the list.
 */
    class Filter
    {
    public:
        /**
         * @brief Default constructor.
         */
        Filter() = default;

        /**
         * @brief Adds a new filter element to this filter.
         *
         * @param elem Pointer to the filter element to add.
         */
        void AddElement(FilterElement* elem);

        /**
         * @brief Checks if a packet matches all filter elements.
         *
         * @param packet The packet to test against the filter.
         * @return True if the packet matches all elements, false otherwise.
         */
        bool Match(Ptr<Packet> packet);

    private:
        std::vector<FilterElement*> m_elements; ///< List of filter elements for this filter.
    };

} // namespace ns3

#endif //FILTER_H
