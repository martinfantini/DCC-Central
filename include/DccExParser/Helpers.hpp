#ifndef __DCC_EX_HELPERS_HPP__
#define __DCC_EX_HELPERS_HPP__

#include "TrackInterface.hpp"

#include <string>

namespace DccExParser::Helpers
{
    std::string DccTrackStatus(DccExParser::TrackInterface& _trackInterface);
    void emergencyStop(DccExParser::TrackInterface& _trackInterface);
}

#endif
