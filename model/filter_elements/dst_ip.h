//
// Created by shun on 4/16/25.
//

#ifndef DST_IP_H
#define DST_IP_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"

class dst_ip {
private:
    ns3::Ipv4Address value;

public:
    DstIP(ns3::Ipv4Address addr);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //DST_IP_H
