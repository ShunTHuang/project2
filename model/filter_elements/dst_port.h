//
// Created by shun on 4/16/25.
//

#ifndef DST_PORT_H
#define DST_PORT_H

#include "FilterElement.h"
#include "ns3/packet.h"

namespace ns3 {
    class DstPort : public FilterElement
    {
    public:
        explicit DstPort(uint32_t port);
        bool Match(Ptr<Packet> packet) override;

    private:
        uint32_t m_port;
    };
}
#endif //DST_PORT_H