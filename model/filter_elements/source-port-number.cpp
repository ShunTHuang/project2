/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "source-port-number.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    /**
     * @brief Constructor that store port number to match.
     *
     * @param port Source port value to compare.
     */
    SourcePortNumber::SourcePortNumber(uint32_t port)
        : m_port(port)
    {
    }

    /**
     * @brief Check if the packet's source port match with stored port.
     *
     * It will remove PPP and IP headers, then check protocol.
     * If TCP or UDP, it will peek transport header and compare source port.
     *
     * @param packet The packet to evaluate.
     * @return True if match; false otherwise.
     */
    bool
    SourcePortNumber::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        copy->RemoveHeader(ipv4Header);

        uint8_t protocol = ipv4Header.GetProtocol();

        if (protocol == 6) // TCP
        {
            TcpHeader tcpHeader;
            if (copy->PeekHeader(tcpHeader))
            {
                return tcpHeader.GetSourcePort() == m_port;
            }
        }
        else if (protocol == 17) // UDP
        {
            UdpHeader udpHeader;
            if (copy->PeekHeader(udpHeader))
            {
                return udpHeader.GetSourcePort() == m_port;
            }
        }

        return false;
    }

} // namespace ns3
