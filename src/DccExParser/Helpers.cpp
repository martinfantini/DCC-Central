#include "Helpers.hpp"
#include <iostream>

namespace DccExParser::Helpers
{
    std::string print_DccTrackStatus(DccExParser::TrackInterface& _trackInterface)
    {
        std::string result;
        bool main_on = _trackInterface.isTrackOn(TrackInterface::TackType::eMain);
        bool prog_on = _trackInterface.isTrackOn(TrackInterface::TackType::eProg);
        bool join_on = _trackInterface.isTrackOn(TrackInterface::TackType::eJoin);
        
        if (main_on && prog_on && join_on)
            result = "<p1 JOIN>\n";
        else if (main_on && prog_on)
            result = "<p1>\n";
        else if (main_on)
            result = "<p1 MAIN>\n";
        else if (prog_on)
            result = "<p1 PROG>\n";
        else
            result = "<p0>\n";
        return result;
    }

    void emergencyStop(DccExParser::TrackInterface& _trackInterface)
    {
        _trackInterface.turnOffTrack(TrackInterface::TackType::eMain);
        _trackInterface.turnOffTrack(TrackInterface::TackType::eProg);
        _trackInterface.turnOffTrack(TrackInterface::TackType::eJoin);
    }

    std::string print_DccSensorStatus(DccExParser::SensorsInterface& _sensors)
    {
        std::string result;
        for (auto sensorStatus : _sensors.getStatusSensors())
        {
            result += "<";
            result += (sensorStatus.second ? "Q" : "q");
            result +=  + " ";
            result += std::to_string(sensorStatus.first) + ">\n";
        }
        return result;
    }

    std::string print_DccInfo(DccExParser::InfoInterface& _info)
    {
        std::string result = "<iDCC-EX V-";
        result += _info.getDCCVersion() + " ";
        result += _info.getAdditionVersionInfo();
        result += ">\n";
        return result;
    }
    
    std::string print_DCCTurnout(DccExParser::TurnoutInterface& _turnout)
    {
        // <H %d %d>\n"),tt->getId(), tt->isThrown());
        return "";
    }

    std::string print_DCCSensorConfiguration(DccExParser::SensorsInterface& _sensors)
    {
        std::string result;
        for (auto sensorConfig : _sensors.getConfigurationSensors())
        {
            result += "<Q ";
            result += std::to_string(sensorConfig.first);
            result += " ";
            result += std::to_string(sensorConfig.second.first);
            result += " ";
            result += (sensorConfig.second.second?"1":"0");
            result += ">\n";
        }
        return result;
    }
}