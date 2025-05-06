/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "src_mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

/**
 * @brief Constructor that take source address and mask.
 *
 * @param address The base source address to compare.
 * @param mask The mask apply to both stored and packet address.
 */
    SrcMask::SrcMask(Ipv4Address address, Ipv4Mask mask)
            : m_address(address),
              m_mask(mask)
    {
    }

/**
 * @brief Check if packet source address match after apply mask.
 *
 * This remove PPP and IP headers, then compare masked address.
 *
 * @param packet The packet to evaluate.
 * @return True if match; false otherwise.
 */
    bool
    SrcMask::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        copy->RemoveHeader(ipv4Header);

        Ipv4Address src = ipv4Header.GetSource();
        Ipv4Address maskedSrc = src.CombineMask(m_mask);
        Ipv4Address maskedExpected = m_address.CombineMask(m_mask);

        return maskedSrc == maskedExpected;
    }

} // namespace ns3
