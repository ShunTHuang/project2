//
// Created by shun on 4/16/25.
//

#ifndef DST_IP_H
#define DST_IP_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

class DstIP : public FilterElement {
private:
    ns3::Ipv4Address value;

public:
    DstIP(ns3::Ipv4Address addr);
    bool match(ns3::Ptr<ns3::Packet> p);
};

#endif //DST_IP_H
