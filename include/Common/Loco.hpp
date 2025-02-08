#ifndef __COMMON_LOCO_INFORMATION_HPP__
#define __COMMON_LOCO_INFORMATION_HPP__

#include <vector>
#include <unordered_map>

namespace Common::LocoInformation
{
    struct LocoFunctionsGroup
    {
        F1_F4 = 0,
        F5_F12,
        F13_F20,
        F21_F28,
    };

    struct LocoInfo
    {
        // This is optional.
        int LocoId = 0;
        // store the actual current
        int currentSpeed = 0;
        // store the current direction
        bool currentDirection = 0;
        // indictor of the group
        LocoFunctionsGroup functionIndicator;
        // current group value
        std::vector<char> functionStatus;
    };

    typedef std::unordered_map<Address, LocoInfo> loco_map_type;
    loco_map_type LocoMap;
}

#endif
