//
// Created by shun on 4/16/25.
//

#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H


#include "ns3/object.h"
#include "ns3/packet.h"

using namespace ns3;

class FilterElement: public ns3::Object
{
public:

    FilterElement ();
    ~FilterElement ();

    virtual bool match(Ptr<Packet> packet) = 0;

};


#endif /* FILTER_ELEMENT_H */