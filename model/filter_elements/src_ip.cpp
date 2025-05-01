//
// Created by shun on 4/16/25.
//

#include "src_ip.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3 {
    SrcIp::SrcIp(Ipv4Address addr)
      : m_address(addr)
    {
    }

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
}