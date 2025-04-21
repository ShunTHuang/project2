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
    Ipv4Address value;

public:
    DstIP(Ipv4Address addr);
    bool match(Ptr<Packet> p);
};

#endif //DST_IP_H
