//
// Created by shun on 4/16/25.
//

#ifndef DST_PORT_H
#define DST_PORT_H

#include "FilterElement.h"
#include "ns3/packet.h"

class DstPort : public FilterElement {
private:
    uint32_t value;

public:
    DstPort(uint32_t port);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //DST_PORT_H
