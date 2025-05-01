//
// Created by shun on 4/16/25.
//

#ifndef FILTER_ELEMENT_H
#define FILTER_ELEMENT_H


#include "ns3/object.h"
#include "ns3/packet.h"

namespace ns3
{

    class FilterElement: public Object
    {
    public:
        FilterElement ();
        ~FilterElement ();

        virtual bool Match(Ptr<Packet> packet) = 0;
    };

} // namespace ns3

#endif /* FILTER_ELEMENT_H */