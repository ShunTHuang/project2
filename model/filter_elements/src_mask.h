//
// Created by shun on 4/16/25.
//

#ifndef SRC_MASK_H
#define SRC_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

namespace ns3 {
    class SrcMask : public FilterElement
    {
    public:
        SrcMask(Ipv4Address address, Ipv4Mask mask);
        bool Match(Ptr<Packet> packet) override;

    private:
        Ipv4Address m_address;
        Ipv4Mask m_mask;
    };
}

#endif //SRC_MASK_H