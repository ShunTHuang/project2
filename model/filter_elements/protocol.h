/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "FilterElement.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * @brief A filter element that check protocol number of IP header.
 *
 * It is useful when you want to filter packet by protocol, like TCP or UDP.
 */
    class Protocol : public FilterElement
    {
    public:
        /**
         * @brief Constructor that store protocol number to match.
         *
         * @param proto Protocol number (for example, 6 for TCP, 17 for UDP).
         */
        explicit Protocol(uint32_t proto);

        /**
         * @brief Check if packet's protocol field match stored protocol number.
         *
         * It will remove IP header and get protocol field. If same with m_protocol,
         * then return true.
         *
         * @param packet The packet to evaluate.
         * @return True if match; false if not.
         */
        bool Match(Ptr<Packet> packet) override;

    private:
        uint32_t m_protocol; ///< Protocol number to check.
    };

} // namespace ns3

#endif // PROTOCOL_H
