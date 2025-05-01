//
// Created by shun on 4/16/25.
//

#include "dst_port.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    DstPort::DstPort(uint32_t port)
      : m_port(port)
    {
    }

    bool
    DstPort::Match(Ptr<Packet> packet)
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