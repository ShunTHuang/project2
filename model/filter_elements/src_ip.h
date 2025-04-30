//
// Created by shun on 4/16/25.
//

#ifndef SRC_IP_H
#define SRC_IP_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

class SrcIp : public FilterElement
{
public:
    explicit SrcIp(Ipv4Address addr);
    bool Match(Ptr<Packet> packet) override;

private:
    Ipv4Address m_address;
};

#endif //SRC_IP_H