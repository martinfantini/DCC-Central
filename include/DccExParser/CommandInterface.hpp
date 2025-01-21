#ifndef __DCC_EX_LOCO_COMMAND_INTERFACE_HPP_
#define __DCC_EX_LOCO_COMMAND_INTERFACE_HPP_

#include "LocoInterface.hpp"
#include "TrackInterface.hpp"

namespace DccExParser
{
    class CommandInterface
    {
        public:
            virtual LocoInterface& getLocosInfo() = 0;
            virtual TrackInterface& getTrackInterface() = 0;
    };
}

#endif
