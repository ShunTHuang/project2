/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H

#include "ns3/object.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * @brief Abstract base class for filter elements.
 *
 * A FilterElement defines a single matching rule that can be used to test
 * whether a packet meets specific criteria. This class is intended to be
 * subclassed with concrete matching logic.
 */
    class FilterElement : public Object
    {
    public:
        /**
         * @brief Constructor.
         */
        FilterElement();

        /**
         * @brief Virtual destructor.
         */
        ~FilterElement();

        /**
         * @brief Pure virtual method to match a packet.
         *
         * Subclasses must implement this method to define the actual matching logic.
         *
         * @param packet The packet to evaluate.
         * @return True if the packet matches the condition; false otherwise.
         */
        virtual bool Match(Ptr<Packet> packet) = 0;
    };

} // namespace ns3

#endif /* FILTER_ELEMENT_H */
