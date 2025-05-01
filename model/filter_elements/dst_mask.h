//
// Created by shun on 4/16/25.
//

#ifndef DST_MASK_H
#define DST_MASK_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

namespace ns3
{

    class DstMask : public FilterElement
    {
    public:
        DstMask(Ipv4Address address, Ipv4Mask mask);
        bool Match(Ptr<Packet> packet) override;

    private:
        Ipv4Address m_address;
        Ipv4Mask m_mask;
    };

} // namespace ns3

#endif //DST_MASK_H