//
// Created by shun on 4/16/25.
//

#ifndef DST_PORT_H
#define DST_PORT_H

#include <cstdint>
#include "FilterElement.h"

class dst_port {
private:
    uint32_t value;

public:
    DstPort(uint32_t port);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //DST_PORT_H
