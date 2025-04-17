//
// Created by shun on 4/16/25.
//

#include "dst_ip.h"


 DstIP::DstIP(ns3::Ipv4Address addr) : value(addr) {}

 bool DstIP::match(ns3::Ptr<ns3::Packet> p) override {
        ns3::Ipv4Header ipv4Header;
        ns3::Ptr<ns3::Packet> packetCopy = p->Copy();
        if (packetCopy->PeekHeader(ipv4Header)
            return ipv4Header.src == value;

        return false;
    }
}