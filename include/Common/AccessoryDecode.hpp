#ifndef __COMMON_ADDRESS_DECODER_INFORMATION_HPP__
#define __COMMON_ADDRESS_DECODER_INFORMATION_HPP__

#include <vector>
#include <unordered_map>

namespace Common::AddresDecoderInformation
{
    struct Accessory
    {
        int Address;
        int SubAddress;
        bool isActive;
        bool isOn;
    };

}

#endif
