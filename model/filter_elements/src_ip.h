//
// Created by shun on 4/16/25.
//

#ifndef SRC_IP_H
#define SRC_IP_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

class SrcIP : public FilterElement {
    private:
        ns3::Ipv4Address value;

    public:
        SrcIP(ns3::Ipv4Address addr);
        bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //SRC_IP_H
