#ifndef __COMMON_ADDRESS_INFORMATION_HPP__
#define __COMMON_ADDRESS_INFORMATION_HPP__

#include <unordered_set>
#include <string>

namespace Common
{
    struct Accessory
    {
        int Address;
        int SubAddress;
        bool isActive =  false;
        bool isOn = false;

        bool operator==(const Accessory &other) const
        {
            return (this->Address == other.Address && this->SubAddress == other.SubAddress);
        }
    };

    struct KeyHasherAccessory
    { 
        std::size_t operator()(const Accessory& key) const
        {
            return std::hash<int>()(key.Address) ^ (std::hash<int>()(key.SubAddress) << 1);
        }
    };

    typedef std::unordered_set<Accessory, KeyHasherAccessory> Accessory_Set_Type;
}

#endif
