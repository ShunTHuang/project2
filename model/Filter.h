//
// Created by shun on 4/16/25.
//

#ifndef FILTER_H
#define FILTER_H


#include "FilterElement.h"

namespace ns3 {

    class Filter
    {
    public:
        Filter() = default;

        void AddElement(FilterElement* elem);
        bool Match(Ptr<Packet> packet);

    private:
        std::vector<FilterElement*> m_elements;
    };

} // namespace ns3
#endif //FILTER_H