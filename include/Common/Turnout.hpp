#ifndef __COMMON_TURNTABLE_INFORMATION_HPP__
#define __COMMON_TURNTABLE_INFORMATION_HPP__

#include <unordered_map>

namespace Common::TurnoutInformation
{
    enum StatusTurnout
    {
      None = 0,
      Close,
      Throw,
    };

    struct Turnout
    {
        int Address;
        int Pin;
        StatusTurnout Status = StatusTurnout::None;
    };
}

#endif
