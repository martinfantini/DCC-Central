#ifndef __DCC_PROTOCOL_DCC_CONSTANTS_HPP__
#define __DCC_PROTOCOL_DCC_CONSTANTS_HPP__

namespace DccProtocol::DccConstants
{
    constexpr int HIGHEST_SHORT_ADDR = 127;

    // NMRA standard extended packets, payload size WITHOUT checksum.
    constexpr int MAX_PACKET_SIZE = 5;
}

#endif