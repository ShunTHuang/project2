/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "dst_ip.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    /**
     * @brief Constructor.
     *
     * @param addr The destination IP address to match.
     */
    DstIp::DstIp(Ipv4Address addr)
        : m_address(addr)
    {
    }

    /**
     * @brief Check if the given packet matches the destination IP address.
     *
     * @param packet The packet to evaluate.
     * @return True if the destination IP matches; false otherwise.
     */
    bool
    DstIp::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        if (copy->PeekHeader(ipv4Header))
        {
            return ipv4Header.GetDestination() == m_address;
        }

        return false;
    }

} // namespace ns3
