//
// Created by shun on 4/16/25.
//

#include "dst_mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

namespace ns3
{

    DstMask::DstMask(Ipv4Address address, Ipv4Mask mask)
      : m_address(address),
        m_mask(mask)
    {
    }

    bool
    DstMask::Match(Ptr<Packet> packet)
    {
        Ptr<Packet> copy = packet->Copy();
        PppHeader pppHeader;
        Ipv4Header ipv4Header;

        copy->RemoveHeader(pppHeader);
        copy->RemoveHeader(ipv4Header);

        Ipv4Address dst = ipv4Header.GetDestination();
        Ipv4Address maskedDst = dst.CombineMask(m_mask);
        Ipv4Address maskedTarget = m_address.CombineMask(m_mask);

        return maskedDst == maskedTarget;
    }

} // namespace ns3