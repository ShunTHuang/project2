//
// Created by koichi on 4/20/25.
//

#ifndef GLOBAL_DEFAULTS_H
#define GLOBAL_DEFAULTS_H

#include <cstdint>
#include <string>

namespace GlobalDefaults {
    static const std::string DEFAULT_SRC_IP   = "10.1.1.10";
    static const uint16_t    DEFAULT_SRC_PORT = 40000;

    static const std::string DEFAULT_DST_IP   = "10.1.2.21";
    static const uint16_t    DEFAULT_DST_PORT = 50000;

    static const std::string DEFAULT_PROTOCOL = "tcp";
} // namespace GlobalDefaults

#endif // GLOBAL_DEFAULTS_H
