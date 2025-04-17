//
// Created by shun on 4/16/25.
//

#ifndef SRC_IP_H
#define SRC_IP_H

#include "FilterElement.h"
#include "ipv4-address.h"
#include "packet.h"

class SrcIp : public FilterElement {
    private:
        ns3::Ipv4Address value;

    public:
        SrcIP(ns3::Ipv4Address addr);
        bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //SRC_IP_H
