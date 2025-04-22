//
// Created by shun on 4/16/25.
//

#ifndef FILTER_H
#define FILTER_H


#include "FilterElement.h"

class Filter
{
private:
    std::vector<FilterElement*> elements;

public:
    Filter() = default;

    void
    AddElement(FilterElement* elem)
    {
        elements.push_back(elem);
    }

    bool match(Ptr<Packet> p);
};



#endif //FILTER_H
