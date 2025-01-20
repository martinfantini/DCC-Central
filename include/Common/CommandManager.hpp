#ifndef __COMMON_COMMAND_MANAGER_HPP_
#define __COMMON_COMMAND_MANAGER_HPP_

#include "Loco.hpp"

namespace Common
{
    // This is the interface of command manager
    class CommandManager
    {
        public:
            // To seach and create a new loco
            virtual std::pair<bool, Loco> lookupLocos(int locoId, bool autoCreate = false) = 0;
            virtual void setThrottle(int cab, int tspeed, int direction) = 0;
            virtual bool setFunction(int cab, int functionNumber, bool on) = 0;
            virtual int getMaxLocos() = 0;
    };
}

#endif

