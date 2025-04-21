//
// Created by shun on 4/16/25.
//

#include "dst_port.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/ppp-header.h"

DstPort::DstPort(uint32_t port)
    : value(port) {}

bool DstPort::match(ns3::Ptr<ns3::Packet> packet) {
    Ptr<Packet> copyPacket = packet->Copy();
    PppHeader pppHeader;
    Ipv4Header ipv4Header;


    copyPacket->RemoveHeader(pppHeader);
    copyPacket->RemoveHeader(ipv4Header);
    uint8_t protocol = ipv4Header.GetProtocol();

    if (protocol == 6) {  // TCP
        ns3::TcpHeader tcpHeader;
        if (copyPacket->PeekHeader(tcpHeader)) {
            NS_LOG_UNCOND("[port] match() called, tcp dport="
                                  << tcpHeader.GetDestinationPort());

            return tcpHeader.GetDestinationPort() == value;
        }
    } else if (protocol == 17) {  // UDP
        ns3::UdpHeader udpHeader;
        if (copyPacket->PeekHeader(udpHeader)) {
            return udpHeader.GetDestinationPort() == value;
        }
    }

    return false;
}


