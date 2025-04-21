//
// Created by shun on 4/16/25.
//

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "FilterElement.h"
#include "ns3/packet.h"

class Protocol : public FilterElement {
private:
    uint32_t value;

public:
    Protocol(uint32_t proto);
    bool match(Ptr<Packet> p) override;
};



#endif //PROTOCOL_H
