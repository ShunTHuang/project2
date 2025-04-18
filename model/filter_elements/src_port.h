//
// Created by shun on 4/16/25.
//

#ifndef SRC_PORT_H
#define SRC_PORT_H

#include "FilterElement.h"
#include "packet.h"

class SrcPort : public FilterElement {
private:
    uint32_t value;

public:
    SrcPort(uint32_t port);
    bool match(ns3::Ptr<ns3::Packet> p) override;
};

#endif //SRC_PORT_H
