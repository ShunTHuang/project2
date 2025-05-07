/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef SRC_MASK_H
#define SRC_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

namespace ns3
{

/**
 * @brief A filter element that check source IP with mask.
 *
 * It use mask to compare part of IP address from packet.
 * This is useful to match subnet instead of full address.
 */
    class SrcMask : public FilterElement
    {
    public:
        /**
         * @brief Constructor that take source address and mask.
         *
         * @param address The base source address to compare.
         * @param mask The mask apply to both stored and packet address.
         */
        SrcMask(Ipv4Address address, Ipv4Mask mask);

        /**
         * @brief Check if packet source address match after apply mask.
         *
         * This remove PPP and IP headers, then compare masked address.
         *
         * @param packet The packet to evaluate.
         * @return True if match; false otherwise.
         */
        bool Match(Ptr<Packet> packet) override;

    private:
        Ipv4Address m_address; ///< The base address to compare.
        Ipv4Mask m_mask;       ///< The mask apply to both addresses.
    };

} // namespace ns3

#endif //SRC_MASK_H
