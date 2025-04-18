//
// Created by shun on 4/16/25.
//

#ifndef FILTERELEMENT_H
#define FILTERELEMENT_H

#include "packet.h"
#include "ptr.h"

class FilterElement {
public:
    virtual bool match(ns3::Ptr<ns3::Packet> p) = 0;
    virtual ~FilterElement() {}
};



#endif //FILTERELEMENT_H
