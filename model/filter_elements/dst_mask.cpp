/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "dst_mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    /**
     * @brief Constructor that takes IP address and mask.
     *
     * @param address The base IP address to match with mask.
     * @param mask The IPv4 mask to use for compare.
     */
    DstMask::DstMask(Ipv4Address address, Ipv4Mask mask)
            : m_address(address),
              m_mask(mask)
    {
    }

    /**
     * @brief Check if packet's destination address match the given address with mask.
     *
     * First it will remove PPP and IP headers, then get destination address.
     * It applies mask to both target address and packet one. If same, return true.
     *
     * @param packet The packet that will be checked.
     * @return True if destination address matched after mask apply; false if not.
     */
    bool
    DstMask::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        copy->RemoveHeader(ipv4Header);

        Ipv4Address dst = ipv4Header.GetDestination();
        Ipv4Address maskedDst = dst.CombineMask(m_mask);
        Ipv4Address maskedTarget = m_address.CombineMask(m_mask);

        return maskedDst == maskedTarget;
    }

} // namespace ns3