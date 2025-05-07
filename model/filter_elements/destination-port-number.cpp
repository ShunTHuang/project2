/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "destination-port-number.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    /**
     * @brief Constructor that set the port to match.
     *
     * @param port Destination port number to compare.
     */
    DestinationPortNumber::DestinationPortNumber(uint32_t port)
        : m_port(port)
    {
    }

    /**
     * @brief Check if packet's destination port match stored port.
     *
     * This will extract transport header and see if destination port
     * is equal to m_port.
     *
     * @param packet The packet to test.
     * @return True if match; otherwise false.
     */
    bool
    DestinationPortNumber::Match(Ptr<Packet> packet)
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
                return tcpHeader.GetDestinationPort() == m_port;
            }
        }
        else if (protocol == 17) // UDP
        {
            UdpHeader udpHeader;
            if (copy->PeekHeader(udpHeader))
            {
                return udpHeader.GetDestinationPort() == m_port;
            }
        }

        return false;
    }

} // namespace ns3
