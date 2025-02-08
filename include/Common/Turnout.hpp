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
        int VirtualPin;
        StatusTurnout Status = StatusTurnout::None;
    };

    // this map stores Address and Turnout
    typedef std::unordered_map<int, Turnout> turnout_map_type;
    turnout_map_type TurnoutMap;
}

#endif
