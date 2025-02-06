#ifndef __DCC_PROTOCOL_DCC_CONSTANTS_HPP__
#define __DCC_PROTOCOL_DCC_CONSTANTS_HPP__

namespace DccProtocol::DccConstants
{
    constexpr int HIGHEST_SHORT_ADDR = 127;
    constexpr int LONG_ADDR_MARKER = 0x4000;

    // NMRA standard extended packets, payload size WITHOUT checksum.
    constexpr int MAX_PACKET_SIZE = 5;

    // NMRA codes #
    constexpr char SET_SPEED = 0x3f;
    constexpr char WRITE_BYTE_MAIN = 0xEC;
    constexpr char WRITE_BIT_MAIN = 0xE8;
    constexpr char WRITE_BYTE = 0x7C;
    constexpr char VERIFY_BYTE = 0x74;
    constexpr char BIT_MANIPULATE = 0x78;
    constexpr char WRITE_BIT = 0xF0;
    constexpr char VERIFY_BIT = 0xE0;
    constexpr char BIT_ON = 0x08;
    constexpr char BIT_OFF = 0x00;
}

#endif