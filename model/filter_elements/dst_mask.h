/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef DST_MASK_H
#define DST_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

namespace ns3
{

/**
 * @brief This class is for matching packet by masked IP address.
 *
 * It will check destination IP address of packet and compare with
 * stored IP and mask. If masked value is same, then packet is matched.
 */
    class DstMask : public FilterElement
    {
    public:
        /**
         * @brief Constructor that takes IP address and mask.
         *
         * @param address The base IP address to match with mask.
         * @param mask The IPv4 mask to use for compare.
         */
        DstMask(Ipv4Address address, Ipv4Mask mask);

        /**
         * @brief Check if packet's destination address match the given address with mask.
         *
         * @param packet The packet that will be checked.
         * @return True if destination address matched after mask apply; false if not.
         */
        bool Match(Ptr<Packet> packet) override;

    private:
        Ipv4Address m_address; ///< Base address to do match.
        Ipv4Mask m_mask;       ///< Mask used to compare with packet address.
    };

} // namespace ns3

#endif // DST_MASK_H