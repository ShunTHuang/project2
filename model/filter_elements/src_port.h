//
// Created by shun on 4/16/25.
//

#ifndef SRC_PORT_H
#define SRC_PORT_H

#include "FilterElement.h"
#include "ns3/packet.h"

namespace ns3
{

    class SrcPort : public FilterElement
    {
    public:
        explicit SrcPort(uint32_t port);
        bool Match(Ptr<Packet> packet) override;

    private:
        uint32_t m_port;
    };

} // namespace ns3

#endif //SRC_PORT_H