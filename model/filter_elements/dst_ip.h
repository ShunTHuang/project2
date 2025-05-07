/*
 * Copyright (c) 2025 shun-peter-koichi.code
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * Author: Shun <shuang86@dons.usfca.edu>
 */

#ifndef DST_IP_H
#define DST_IP_H

#include "filter-element.h"
#include "ns3/ipv4-address.h"
#include "ns3/packet.h"
#include "ns3/ptr.h"

namespace ns3
{

    /**
     * @brief Filter element that matches packets based on destination IP address.
     *
     * This class implements the FilterElement interface and checks whether
     * a given packet's destination IP address matches a specified target address.
     */
    class DstIp : public FilterElement
    {
    private:
        Ipv4Address m_address; ///< IP address to match against.

    public:
        /**
         * @brief Constructor.
         *
         * @param addr The destination IP address to match.
         */
        DstIp(Ipv4Address addr);

        /**
         * @brief Check if the given packet matches the destination IP address.
         *
         * @param packet The packet to evaluate.
         * @return True if the destination IP matches; false otherwise.
         */
        bool Match(Ptr<Packet> packet);
    };

} // namespace ns3

#endif //DST_IP_H