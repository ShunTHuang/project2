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

using json = nlohmann::json;

namespace ns3
{

    class QoSCreator
    {
    public:
        std::vector<TrafficClass*> CreateTrafficClasses(const std::string& filename);
        DiffServ* CreateQoS(const std::string& filename);

    private:
        void ParseFilters(const json& filtersConfig, TrafficClass* tc);
    };

} // namespace ns3

#endif // QOSCREATOR_H