//
// Created by shun on 4/16/25.
//

#ifndef DST_MASK_H
#define DST_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

class DstMask : public FilterElement {
private:
    Ipv4Address addr;
    Ipv4Mask mask;

public:
    DstMask(Ipv4Address address, Ipv4Mask m);
    bool match(Ptr<Packet> p) override;
};

#endif //DST_MASK_H
