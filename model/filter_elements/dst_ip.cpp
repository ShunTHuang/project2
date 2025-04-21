//
// Created by shun on 4/16/25.
//

#include "dst_ip.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

DstIP::DstIP(Ipv4Address addr) : value(addr) {}

bool DstIP::match(Ptr<Packet> p) {
    PppHeader pppHeader;
    Ipv4Header ipv4Header;
    Ptr<Packet> packetCopy = p->Copy();

    packetCopy->RemoveHeader(pppHeader);
    if (packetCopy->PeekHeader(ipv4Header)) {
        NS_LOG_UNCOND("[DstIP] IP: " << ipv4Header.GetSource());
        return ipv4Header.GetSource() == value;
    }

    return false;
}
