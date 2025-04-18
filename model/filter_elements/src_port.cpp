//
// Created by shun on 4/16/25.
//

#include "src_port.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"

SrcPort::SrcPort(uint32_t port)
    : value(port) {}

bool SrcPort::match(ns3::Ptr<ns3::Packet> p) {
    ns3::Ipv4Header ipv4Header;
    ns3::Ptr<ns3::Packet> packetCopy = p->Copy();

    if (!packetCopy->PeekHeader(ipv4Header)) {
        return false;
    }

    packetCopy->RemoveHeader(ipv4Header);
    uint8_t protocol = ipv4Header.GetProtocol();

    if (protocol == 6) {  // TCP
        ns3::TcpHeader tcpHeader;
        if (packetCopy->PeekHeader(tcpHeader)) {
            return tcpHeader.GetSourcePort() == value;
        }
    } else if (protocol == 17) {  // UDP
        ns3::UdpHeader udpHeader;
        if (packetCopy->PeekHeader(udpHeader)) {
            return udpHeader.GetSourcePort() == value;
        }
    }

    return false;
}
