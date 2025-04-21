//
// Created by shun on 4/16/25.
//

#include "dst_mask.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

DstMask::DstMask(Ipv4Address address, Ipv4Mask m)
    : addr(address),
      mask(m)
{
}

bool
DstMask::match(Ptr<Packet> p)
{
    PppHeader pppHeader;
    Ipv4Header ipv4Header;
    Ptr<Packet> packetCopy = p->Copy();

    packetCopy->RemoveHeader(pppHeader);
    packetCopy->RemoveHeader(ipv4Header);

    Ipv4Address src = ipv4Header.GetSource();
    NS_LOG_UNCOND("[DstMask] match() called");
    NS_LOG_UNCOND("[DstMask] Source IP = " << src);
    NS_LOG_UNCOND("[DstMask] Masked = " << src.CombineMask(mask));

    return src.CombineMask(mask) == addr.CombineMask(mask) && src == addr;
}