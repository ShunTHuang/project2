//
// Created by shun on 4/16/25.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>

#include "FilterElement.h"

class protocol {
private:
    uint32_t value;

public:
    Protocol(uint32_t proto);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};



#endif //PROTOCOL_H
