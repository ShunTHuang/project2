//
// Created by shun on 4/16/25.
//

#include "src_mask.h"
#include "ipv4-header.h"

SrcMask::SrcMask(ns3::Ipv4Address address, ns3::Ipv4Mask m)
    : addr(address), mask(m) {}

bool SrcMask::match(ns3::Ptr<ns3::Packet> p) {
    ns3::Ipv4Header ipv4Header;
    ns3::Ptr<ns3::Packet> packetCopy = p->Copy();

    if (packetCopy->PeekHeader(ipv4Header)) {
        ns3::Ipv4Address src = ipv4Header.GetSource();
        return src.CombineMask(mask) == addr.CombineMask(mask);
    }

    return false;
}
