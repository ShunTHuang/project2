/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef DST_PORT_H
#define DST_PORT_H

#include "FilterElement.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * @brief This class try to match packet by destination port number.
 *
 * It looks inside transport layer header (like UDP or TCP)
 * and compare port with the value stored.
 */
    class DstPort : public FilterElement
    {
    public:
        /**
         * @brief Constructor that set the port to match.
         *
         * @param port Destination port number to compare.
         */
        explicit DstPort(uint32_t port);

        /**
         * @brief Check if packet's destination port match stored port.
         *
         * This will extract transport header and see if destination port
         * is equal to m_port.
         *
         * @param packet The packet to test.
         * @return True if match; otherwise false.
         */
        bool Match(Ptr<Packet> packet) override;

    private:
        uint32_t m_port; ///< Port number to match with packet.
    };

} // namespace ns3

#endif // DST_PORT_H
