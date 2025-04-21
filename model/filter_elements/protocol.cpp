//
// Created by shun on 4/16/25.
//

#include "protocol.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

Protocol::Protocol(uint32_t proto)
    : value(proto) {}

bool Protocol::match(ns3::Ptr<ns3::Packet> packet) {
    Ptr<Packet> copy = packet->Copy();
    PppHeader pppHeader;
    Ipv4Header ipv4Header;
    copy->RemoveHeader(pppHeader);
    copy->PeekHeader(ipv4Header);

    uint16_t protocolNumber = ipv4Header.GetProtocol();
    NS_LOG_UNCOND("[protocol] match() called, protocolNumber="
                          << protocolNumber);
    NS_LOG_UNCOND("[protocol] match() called, value="
                          << value);
    return protocolNumber == value;
}
