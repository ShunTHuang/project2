/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef SPQGENERATOR_H
#define SPQGENERATOR_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ns3
{

/**
 * @brief Represent one SPQ rule extracted from CLI.
 *
 * This include destination port, DSCP value, and assigned queue number.
 */
    struct Rule {
        int dstPort; ///< Destination port number to match.
        int dscp;    ///< DSCP value to set.
        int queue;   ///< Queue index this rule belongs to.
    };

/**
 * @brief Parser class that generate SPQ config file from CLI.
 *
 * This class reads simple CLI rule and convert into structured JSON file
 * that can be used by simulator.
 */
    class CLIParser
    {
    public:
        /**
         * @brief Generate JSON config file from CLI command file.
         *
         * @param cliFilePath Path to CLI input file.
         * @param jsonOutputPath Path to write JSON output.
         * @return True if successful; otherwise false.
         */
        bool GenerateSpqConfig(const std::string& cliFilePath,
                               const std::string& jsonOutputPath);
    };

} // namespace ns3

#endif // SPQGENERATOR_H
