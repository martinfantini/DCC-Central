#ifndef __COMMON_TURNTABLE_INFORMATION_HPP__
#define __COMMON_TURNTABLE_INFORMATION_HPP__

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
        int VirtualPin;
        StatusTurnout Status = StatusTurnout::None;
    };
 
    typedef std::unordered_map<Address, Turnout> turnout_map_type;
    turnout_map_type TurnoutMap;
}

#endif
