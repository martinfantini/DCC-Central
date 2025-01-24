#ifndef __DCC_EX_HELPERS_HPP__
#define __DCC_EX_HELPERS_HPP__

#include "TrackInterface.hpp"
#include "InfoInterface.hpp"
#include "SensorsInterface.hpp"
#include "TurnoutInterface.hpp"


#include <string>

namespace DccExParser::Helpers
{
    // Print functions for dcc
    std::string print_DccTrackStatus(DccExParser::TrackInterface& _trackInterface);
    std::string print_DccSensorStatus(DccExParser::SensorsInterface& _sensors);
    std::string print_DCCSensorConfiguration(DccExParser::SensorsInterface& _sensors);
    std::string print_DccInfo(DccExParser::InfoInterface& _info);
    std::string print_DCCTurnout(DccExParser::TurnoutInterface& _turnout);

    // To generate the emergency stop.
    void emergencyStop(DccExParser::TrackInterface& _trackInterface);
}

#endif
