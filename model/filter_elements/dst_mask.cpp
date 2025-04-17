//
// Created by shun on 4/16/25.
//

#include "dst_mask.h"

DstMask::DstMask(ns3::Ipv4Address address, ns3::Ipv4Mask m)
    : addr(address), mask(m) {}

bool DstMask::match(ns3::Ptr<ns3::Packet> p) {
    ns3::Ipv4Header ipv4Header;
    ns3::Ptr<ns3::Packet> packetCopy = p->Copy();

    if (packetCopy->PeekHeader(ipv4Header)) {
        ns3::Ipv4Address dst = ipv4Header.GetDestination();
        return dst.CombineMask(m) == addr.CombineMask(mask);
    }

    return false;
}
