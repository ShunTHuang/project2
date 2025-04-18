//
// Created by shun on 4/16/25.
//

#include "src_ip.h"
#include "ipv4-header.h"


SrcIP::SrcIP(ns3::Ipv4Address addr) : value(addr) {}

bool SrcIP::match(ns3::Ptr<ns3::Packet> p) {
    ns3::Ipv4Header ipv4Header;
    ns3::Ptr<ns3::Packet> packetCopy = p->Copy();

    if (packetCopy->PeekHeader(ipv4Header)) {
        return ipv4Header.GetSource() == value;
    }

    return false;
}