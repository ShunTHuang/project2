//
// Created by shun on 4/16/25.
//

#ifndef DST_IP_H
#define DST_IP_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

namespace ns3 {
    class DstIp : public FilterElement
    {
    private:
        Ipv4Address m_address;

    public:
        DstIp(Ipv4Address addr);
        bool Match(Ptr<Packet> packet);
    };
}

#endif //DST_IP_H