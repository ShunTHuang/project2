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
        Ipv4Address value;

    public:
        SrcIP(Ipv4Address addr);
        bool match(Ptr<Packet> p) override;
};



#endif //SRC_IP_H
