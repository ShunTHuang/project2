//
// Created by koichi on 4/18/25.
//

#ifndef QOSCREATOR_H
#define QOSCREATOR_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "TrafficClass.h"
#include "DiffServ.h"
#include "StrictPriorityQueue.h"
#include "DeficitRoundRobin.h"

using json = nlohmann::json;

class QoSCreator {
public:
    std::vector<TrafficClass*> createTrafficClasses(const std::string& filename);

    DiffServ* createQoS(const std::string& filename);

private:
    void parseFilters(const json& filtersConfig, TrafficClass* tc);
};

#endif // QOSCREATOR_H