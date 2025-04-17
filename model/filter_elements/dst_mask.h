//
// Created by shun on 4/16/25.
//

#ifndef DST_MASK_H
#define DST_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-mask.h"
#include "ns3/ipv4-address.h"

class dst_mask {
private:
    ns3::Ipv4Address addr;
    ns3::Ipv4Mask mask;

public:
    DstMask(ns3::Ipv4Address address, ns3::Ipv4Mask m);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //DST_MASK_H
