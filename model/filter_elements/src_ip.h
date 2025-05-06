/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef SRC_IP_H
#define SRC_IP_H

#include "FilterElement.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"

namespace ns3
{

/**
 * @brief Filter that check source IP address of a packet.
 *
 * This class will look at the IP header and compare source address
 * to the one stored in this filter.
 */
    class SrcIp : public FilterElement
    {
    public:
        /**
         * @brief Constructor with IP address to match.
         *
         * @param addr Source IP address you want to match.
         */
        explicit SrcIp(Ipv4Address addr);

        /**
         * @brief Check if the packet's source IP match stored address.
         *
         * Remove PPP and IP headers to get source IP from packet.
         * If same with m_address, then match success.
         *
         * @param packet The packet to evaluate.
         * @return True if matched; false if not.
         */
        bool Match(Ptr<Packet> packet) override;

    private:
        Ipv4Address m_address; ///< The address to compare with source IP.
    };

} // namespace ns3

#endif // SRC_IP_H
