//
// Created by shun on 4/16/25.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "FilterElement.h"
#include "ns3/packet.h"

namespace ns3 {

    class Protocol : public FilterElement
    {
    public:
        explicit Protocol(uint32_t proto);
        bool Match(Ptr<Packet> packet) override;

    private:
        uint32_t m_protocol;
    };

} // namespace ns3

#endif //PROTOCOL_H