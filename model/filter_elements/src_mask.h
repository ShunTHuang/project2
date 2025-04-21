//
// Created by shun on 4/16/25.
//

#ifndef SRC_MASK_H
#define SRC_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

class SrcMask : public FilterElement
{
private:
    Ipv4Address addr;
    Ipv4Mask mask;

public:
    SrcMask(Ipv4Address address, Ipv4Mask m);
    bool match(Ptr<Packet> p) override;
};



#endif //SRC_MASK_H
