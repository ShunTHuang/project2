//
// Created by shun on 4/16/25.
//

#include "protocol.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    Protocol::Protocol(uint32_t protocol)
      : m_protocol(protocol)
    {
    }

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