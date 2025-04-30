//
// Created by shun on 4/16/25.
//

#include "src_mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

SrcMask::SrcMask(Ipv4Address address, Ipv4Mask mask)
  : m_address(address),
    m_mask(mask)
{
}

bool
SrcMask::Match(Ptr<Packet> packet)
{
    Ptr<Packet> copy = packet->Copy();
    PppHeader pppHeader;
    Ipv4Header ipv4Header;

    copy->RemoveHeader(pppHeader);
    copy->RemoveHeader(ipv4Header);

    Ipv4Address src = ipv4Header.GetSource();
    Ipv4Address maskedSrc = src.CombineMask(m_mask);
    Ipv4Address maskedExpected = m_address.CombineMask(m_mask);

    return maskedSrc == maskedExpected;
}