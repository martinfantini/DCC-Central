#ifndef __DCC_EX_LOCO_COMMAND_INTERFACE_HPP_
#define __DCC_EX_LOCO_COMMAND_INTERFACE_HPP_

#include "LocoInterface.hpp"
#include "TrackInterface.hpp"
#include "InfoInterface.hpp"
#include "SensorsInterface.hpp"
#include "TurnoutInterface.hpp"

namespace DccExParser
{
    class CommandInterface
    {
        public:
            virtual LocoInterface& getLocosInfo() = 0;
            virtual TrackInterface& getTrackInterface() = 0;
            virtual SensorsInterface& getSensors() = 0;
            virtual TurnoutInterface& getTurnout() = 0;
            virtual InfoInterface& getInfo() = 0;
    };
}

#endif
