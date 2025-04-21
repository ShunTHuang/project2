//
// Created by shun on 4/16/25.
//

#include "src_ip.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

SrcIP::SrcIP(Ipv4Address addr)
    : value(addr)
{
}

bool
SrcIP::match(Ptr<Packet> p)
{
    PppHeader pppHeader;
    Ipv4Header ipv4Header;
    Ptr<Packet> packetCopy = p->Copy();

    packetCopy->RemoveHeader(pppHeader);
    if (packetCopy->PeekHeader(ipv4Header))
    {
        NS_LOG_UNCOND("[SrcIP] IP: " << ipv4Header.GetSource());
        return ipv4Header.GetSource() == value;
    }
    return false;
}