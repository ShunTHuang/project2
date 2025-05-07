/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#include "CLIParser.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <regex>

namespace ns3
{

// Map DSCP to COS values
    int
    GetCosFromDscp(int dscp)
    {
        switch (dscp)
        {
            case 46:
                return 5;
            case 8:
                return 1;
            default:
                return 0;
        }
    }

// Map COS to queue index
    int
    GetQueueFromCos(int cos)
    {
        switch (cos)
        {
            case 5:
                return 1;
            case 1:
                return 2;
            default:
                return 0;
        }
    }

// Parse the CLI file and build Rule list
    std::vector<Rule>
    ParseCliFile(const std::string& filename)
    {
        std::ifstream infile(filename);
        if (!infile)
        {
            return {};
        }

        std::regex accessListRe (R"(^\s*access-list\s+(\d+)\s+permit\s+udp\s+any\s+any\s+eq\s+(\d+))");
        std::regex classMapRe   (R"(^\s*class-map\s+match-all\s+(\S+))");
        std::regex matchAclRe   (R"(^\s*match\s+access-group\s+(\d+))");
        std::regex policyClassRe(R"(^\s*class\s+(\S+)\s*$)");
        std::regex setDscpRe    (R"(^\s*set\s+dscp\s+(\d+))");

        std::unordered_map<int, int> aclToPort;
        std::unordered_map<std::string, int> classToAcl;
        std::unordered_map<std::string, int> classToDscp;

        std::string currentClass;
        std::string currentPolicyClass;
        std::string line;

        while (std::getline(infile, line))
        {
            std::smatch m;
            if (std::regex_search(line, m, accessListRe))
            {
                aclToPort[std::stoi(m[1])] = std::stoi(m[2]);
            }
            else if (std::regex_search(line, m, classMapRe))
            {
                currentClass = m[1];
            }
            else if (std::regex_search(line, m, matchAclRe))
            {
                classToAcl[currentClass] = std::stoi(m[1]);
            }
            else if (std::regex_search(line, m, policyClassRe)
                     && line.find("class-map") == std::string::npos)
            {
                currentPolicyClass = m[1];
            }
            else if (std::regex_search(line, m, setDscpRe))
            {
                classToDscp[currentPolicyClass] = std::stoi(m[1]);
            }
        }

        std::vector<Rule> rules;
        for (auto const& kv : classToAcl)
        {
            const std::string& cls = kv.first;
            int aclId              = kv.second;
            auto itPort = aclToPort.find(aclId);
            auto itDscp = classToDscp.find(cls);
            if (itPort != aclToPort.end() && itDscp != classToDscp.end())
            {
                int port  = itPort->second;
                int dscp  = itDscp->second;
                int cos   = GetCosFromDscp(dscp);
                int queue = GetQueueFromCos(cos);
                if (queue > 0)
                {
                    rules.push_back({port, dscp, queue});
                }
            }
        }

        // Sort by queue index to ensure low-priority first
        std::sort(rules.begin(), rules.end(), [](auto const& a, auto const& b)
        {
            return a.queue < b.queue;
        });

        return rules;
    }

/**
 * @brief Generate JSON config file from CLI command file.
 *
 * @param cliFilePath Path to CLI input file.
 * @param jsonOutputPath Path to write JSON output.
 * @return True if successful; otherwise false.
 */
    bool
    CLIParser::GenerateSpqConfig(const std::string& cliFilePath,
                                 const std::string& jsonOutputPath)
    {
        auto rules = ParseCliFile(cliFilePath);
        if (rules.empty())
        {
            return false;
        }

        nlohmann::json config;
        config["qos_mechanism"] = "spq";
        config["queues"] = nlohmann::json::array();

        for (auto const& r : rules)
        {
            nlohmann::json q;
            q["priority_level"] = (r.queue == 1 ? 0 : 1);
            q["maxPackets"]     = 100;
            q["quantum"]        = 100;
            q["weight"]         = 1;
            q["isDefault"]      = false;

            // Build filter group
            nlohmann::json filter = nlohmann::json::array({
                {{"filterType", "Protocol"}, {"filterValue", "udp"}},
                {{"filterType", "DstPort"},  {"filterValue", r.dstPort}}
            });
            q["filters"] = nlohmann::json::array({filter});
            config["queues"].push_back(q);
        }

        std::ofstream ofs(jsonOutputPath);
        if (!ofs)
        {
            return false;
        }
        ofs << config.dump(2) << std::endl;
        return true;
    }

} // namespace ns3
