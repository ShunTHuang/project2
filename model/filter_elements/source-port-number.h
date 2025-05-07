/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef SRC_PORT_H
#define SRC_PORT_H

#include "filter-element.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * @brief A filter that check the source port of transport layer.
 *
 * This class support match packet by its source port,
 * like if packet is coming from specific UDP or TCP port.
 */
    class SourcePortNumber : public FilterElement
    {
    public:
        /**
         * @brief Constructor that store port number to match.
         *
         * @param port Source port value to compare.
         */
        explicit SourcePortNumber(uint32_t port);

        /**
         * @brief Check if the packet's source port match with stored port.
         *
         * It will remove PPP and IP headers, then check protocol.
         * If TCP or UDP, it will peek transport header and compare source port.
         *
         * @param packet The packet to evaluate.
         * @return True if match; false otherwise.
         */
        bool Match(Ptr<Packet> packet) override;

    private:
        uint32_t m_port; ///< Port number to match with source port of packet.
    };

} // namespace ns3

#endif //SRC_PORT_H