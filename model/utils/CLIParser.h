//
// Created by shun on 5/3/25.
//

#ifndef SPQGENERATOR_H
#define SPQGENERATOR_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace ns3
{

    struct Rule {
        int dstPort;
        int dscp;
        int queue;
    };

    class CLIParser
    {
        public:
            bool GenerateSpqConfig(const std::string& cliFilePath,
                                   const std::string& jsonOutputPath);
    };

} // namespace ns3

#endif //SPQGENERATOR_H
