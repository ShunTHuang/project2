//
// Created by shun on 4/16/25.
//

#include "protocol.h"
#include "ns3/ipv4-header.h"

Protocol::Protocol(uint32_t proto)
    : value(proto) {}

bool Protocol::match(ns3::Ptr<ns3::Packet> p) {
    ns3::Ipv4Header ipv4Header;
    ns3::Ptr<ns3::Packet> packetCopy = p->Copy();

    if (packetCopy->PeekHeader(ipv4Header)) {
        return ipv4Header.GetProtocol() == value;
    }

    return false;
}
