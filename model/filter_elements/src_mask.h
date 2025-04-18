//
// Created by shun on 4/16/25.
//

#ifndef SRC_MASK_H
#define SRC_MASK_H

#include "FilterElement.h"
#include "ipv4-address.h"
#include "packet.h"
#include "ptr.h"

class SrcMask : public FilterElement {
private:
    ns3::Ipv4Address addr;
    ns3::Ipv4Mask mask;

public:
    SrcMask(ns3::Ipv4Address address, ns3::Ipv4Mask m);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //SRC_MASK_H
