/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "protocol.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    /**
     * @brief Constructor that store protocol number to match.
     *
     * @param protocol Protocol number (for example, 6 for TCP, 17 for UDP).
     */
    Protocol::Protocol(uint32_t protocol)
            : m_protocol(protocol)
    {
    }

    /**
     * @brief Check if packet's protocol field match stored protocol number.
     *
     * It will remove IP header and get protocol field. If same with m_protocol,
     * then return true.
     *
     * @param packet The packet to evaluate.
     * @return True if match; false if not.
     */
    bool
    Protocol::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        copy->PeekHeader(ipv4Header);

        uint16_t protocolNumber = ipv4Header.GetProtocol();

        return protocolNumber == m_protocol;
    }

} // namespace ns3
