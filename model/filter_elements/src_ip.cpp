/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "src_ip.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

/**
 * @brief Constructor with IP address to match.
 *
 * @param addr Source IP address you want to match.
 */
    SrcIp::SrcIp(Ipv4Address addr)
        : m_address(addr)
    {
    }

    /**
     * @brief Check if the packet's source IP match stored address.
     *
     * Remove PPP and IP headers to get source IP from packet.
     * If same with m_address, then match success.
     *
     * @param packet The packet to evaluate.
     * @return True if matched; false if not.
     */
    bool
    SrcIp::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        if (copy->PeekHeader(ipv4Header))
        {
            Ipv4Address src = ipv4Header.GetSource();
            return src == m_address;
        }

        return false;
    }

} // namespace ns3
