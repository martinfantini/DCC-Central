#ifndef __DCC_EX_LOCO_COMMAND_INTERFACE_HPP_
#define __DCC_EX_LOCO_COMMAND_INTERFACE_HPP_

#include "LocoInterface.hpp"
#include "TrackInterface.hpp"
#include "InfoInterface.hpp"
#include "SensorsInterface.hpp"
#include "TurnoutInterface.hpp"
#include "AccessoryInterface.hpp"
#include "DccTrackInterface.hpp"

namespace DccExParser
{
    class CommandInterface
    {
        public:
            virtual LocoInterface&      getLocosInterface()     = 0;
            virtual TrackInterface&     getTrackInterface()     = 0;
            virtual SensorsInterface&   getSensorsInterface()   = 0;
            virtual TurnoutInterface&   getTurnoutInterface()   = 0;
            virtual InfoInterface&      getInfoInterface()      = 0;
            virtual AccessoryInterface& getAccessoryInterface() = 0;
            virtual DccTrackInterface&  getDccTrackInterface()  = 0;

            virtual ~CommandInterface(){}
    };
}

#endif
