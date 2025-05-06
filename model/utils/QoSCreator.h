/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Koichi <knakata@dons.usfca.edu>
 */

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

/**
 * @brief Helper class to create QoS components from JSON config file.
 *
 * This class can read JSON file and make traffic classes and QoS scheduler
 * based on what written in the file.
 */
    class QoSCreator
    {
    public:
        /**
         * @brief Parse config file and create list of traffic classes.
         *
         * @param filename Path to JSON config file.
         * @return Vector of pointer to created TrafficClass.
         */
        std::vector<TrafficClass*> CreateTrafficClasses(const std::string& filename);

        /**
         * @brief Create a QoS object (DiffServ) from config file.
         *
         * @param filename Path to JSON config file.
         * @return A pointer to created DiffServ-based queue.
         */
        DiffServ* CreateQoS(const std::string& filename);

    private:
        /**
         * @brief Helper to parse filters section inside traffic class config.
         *
         * @param filtersConfig JSON object with filter data.
         * @param tc Pointer to traffic class to add filters into.
         */
        void ParseFilters(const json& filtersConfig, TrafficClass* tc);
    };

} // namespace ns3

#endif //QOSCREATOR_H
