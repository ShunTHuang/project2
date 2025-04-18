//
// Created by koichi on 4/18/25.
//

#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include "../TrafficClass.h"
#include "../DiffServ.h"
#include "../filter_elements/dst_ip.h"
#include "../filter_elements/dst_mask.h"
#include "../filter_elements/dst_port.h"
#include "../filter_elements/protocol.h"
#include "../filter_elements/src_ip.h"
#include "../filter_elements/src_mask.h"
#include "../filter_elements/src_port.h"
#include <nlohmann/json.hpp>

class QoSCreator {
private:
    static void parseFilters(const nlohmann::json& filtersConfig, TrafficClass* trafficClass);
public:
    static DiffServ* createQoS(const std::string& filename);
};

#endif //JSONPARSER_H
