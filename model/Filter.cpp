//
// Created by shun on 4/16/25.
//

#include "Filter.h"

bool Filter::match(ns3::Ptr<ns3::Packet> p) {
    for (auto elem : elements) {
        if (!elem->match(p)) {
            return false;
        }
    }
    return true;
}