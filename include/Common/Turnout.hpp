#ifndef __COMMON_TURNTABLE_INFORMATION_HPP__
#define __COMMON_TURNTABLE_INFORMATION_HPP__

#include <unordered_map>

namespace Common
{
    enum StatusTurnout
    {
      StatusTurnout_None = 0,
      Close,
      Throw,
    };

    struct Turnout
    {
        int Id;
        int Address;
        int SubAddress = 0;
        int Pin = 0; // In the case it is not 0, the status toggle with the pin
        StatusTurnout Status = StatusTurnout::StatusTurnout_None;
    };
}

#endif
