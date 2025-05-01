//
// Created by shun on 4/16/25.
//

#include "dst_ip.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    DstIp::DstIp(Ipv4Address addr)
      : m_address(addr)
    {
    }

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