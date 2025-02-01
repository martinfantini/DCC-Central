#include "Helpers.hpp"
#include <iostream>

namespace DccExParser::Helpers
{
    std::string print_DCC_Track_Status(DccExParser::TrackInterface& _trackInterface)
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

    std::string print_DCC_Sensor_Status(DccExParser::SensorsInterface& _sensors)
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

    std::string print_DCC_Info(DccExParser::InfoInterface& _info)
    {
        std::string result = "<iDCC-EX V-";
        result += _info.getDCCVersion() + " ";
        result += _info.getAdditionVersionInfo();
        result += ">\n";
        return result;
    }
    
    std::string print_DCC_Turnout(DccExParser::TurnoutInterface& _turnout)
    {
        std::string result;
        for (auto turnoutStatus : _turnout.getTurnoutSensors())
        {
            result += "<H";
            result += std::to_string(turnoutStatus.first);
            result +=  + " ";
            result += (turnoutStatus.second?"1":"0");
            result += ">\n";
        }
        return result;
    }

    std::string print_DCC_Sensor_Configuration(DccExParser::SensorsInterface& _sensors)
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

    std::string print_DCC_Loco_Info(int _cab, int _locoId ,int _tspeed, long _functions)
    {
        std::string result;
        result += "<l " + std::to_string(_locoId) + " ";
        result += std::to_string(_cab) + " ";
        result += std::to_string(_tspeed) + " ";
        result += std::to_string(_functions) + ">\n";
        return result;
    }

    std::string print_DCC_Loco_Status(const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 4)
            return result;

        result += "<T ";
        result += parameters[0] + " ";
        result += parameters[2] + " ";
        result += parameters[3];
        result += ">\n";
        return result;
    }

    std::string print_DCC_Current_On_Main(DccExParser::DccTrackInterface& _dccTruck)
    {
        std::string result;
        result += "<c CurrentMAIN ";
        result += std::to_string(_dccTruck.getCurrentOnMain()) + " ";
        result += "C Milli 0 ";
        result += std::to_string(_dccTruck.getMaxCurrent());
        result += " 1 ";
        result += std::to_string(_dccTruck.getMaxCurrent());
        result += ">\n";
        return result;
    }

    std::string print_Throttle_DCC_Current(DccExParser::DccTrackInterface& _dccTruck)
    {
        std::string result;
        result += "<jI ";
        result += std::to_string(_dccTruck.getCurrentOnMain()) + " ";
        result += std::to_string(_dccTruck.getCurrentOnProg());
        result += ">\n";
        return result;
    }

    std::string print_Throttle_DCC_Turnout_List(DccExParser::TurnoutInterface& _turnout)
    {
        std::string result;
        result += "<jT";
        for (auto _turnoutInfo : _turnout.getTurnoutSensors())
        {
            result += " " + std::to_string(_turnoutInfo.first);
        }
        result += ">\n";
        return result;
    }

    std::string print_Throttle_DCC_Turnout_Info(int _turnoutId, DccExParser::TurnoutInterface& _turnout)
    {
        std::string result;

        auto _found_turnoutId = _turnout.getTurnoutSensors().find(_turnoutId);
        if (_found_turnoutId == _turnout.getTurnoutSensors().end())
            return result;

        result += "<jT";
        result += " " + std::to_string(_found_turnoutId->first);
        result += " ";
        result += (_found_turnoutId->second)?"T":"C";
        result += ">\n";
        return result;
    }

    std::string print_DCC_Read_Byte(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 1)
            return result;

        result += "<v ";
        result += parameters[0];
        result += std::to_string(result_dcc_Data);
        result += ">\n";
        return result;
    }

    std::string print_DCC_Read_Bit(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 2)
            return result;

        result += "<v ";
        result += parameters[0];
        result += parameters[1];
        result += std::to_string(result_dcc_Data);
        result += ">\n";
        return result;
    }

    std::string print_DCC_Write_Bit(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 5)
            return result;

        result += "<r";
        result += parameters[3] + "|";
        result += parameters[4] + "|";
        result += parameters[0] + " ";
        result += parameters[1] + " ";
        result += (result_dcc_Data == 1) ? parameters[2] : "-1";
        result += ">\n";
        return result;
    }

    std::string print_DCC_Read_CV(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 3)
            return result;

        result += "<r";
        result += parameters[1] + "|";
        result += parameters[2] + "|";
        result += parameters[0] + " ";
        result += std::to_string(result_dcc_Data);
        result += ">\n";
        return result;
    }

    std::string print_DCC_Write_write_CV_Byte_4(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 4)
            return result;

        result += "<r";
        result += parameters[2] + "|";
        result += parameters[3] + "|";
        result += parameters[0] + " ";
        result += (result_dcc_Data == 1) ? parameters[1] : "-1";
        return result;
    }

    std::string print_DCC_Write_write_CV_Byte(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 2)
            return result;

        result += "<w ";
        result += parameters[0] + " ";
        result += (result_dcc_Data == 1) ? parameters[1] : "-1";
        result += ">\n";
        return result;
    }

    std::string print_DCC_Write_LocoId(int result_dcc_Data, const std::vector<std::string>& parameters)
    {
        std::string result;

        if (parameters.size() < 1)
            return result;

        result += "<w ";
        result += (result_dcc_Data == 1) ? parameters[0] : "-1";
        result += ">\n";
        return result;
    }

    std::string print_DCC_Read_LocoId(int result_dcc_Data)
    {
        std::string result;

        /**
         * @brief For now, I will leave this const values here, but they have to be moved to
         * some file because they are part of the DCC protocol.
         */
        constexpr int HIGHEST_SHORT_ADDR = 127;
        constexpr int LONG_ADDR_MARKER = 0x4000;

        result += "<r ";
        if (result_dcc_Data < 0)
        {
            result += "-1";
        }
        else
        {
            bool longAddr = result_dcc_Data & LONG_ADDR_MARKER;
            if (longAddr)
                result_dcc_Data =  result_dcc_Data ^ LONG_ADDR_MARKER;

            if (longAddr  && result_dcc_Data <= HIGHEST_SHORT_ADDR )
            {
                result += "LONG " + std::to_string(result_dcc_Data) + " UNSUPPORTED";
            }
            else
            {
                result += std::to_string(result_dcc_Data);
            }
        }
        result += ">\n";
        return result;
    }

    void emergencyStop(DccExParser::TrackInterface& _trackInterface)
    {
        _trackInterface.turnOffTrack(TrackInterface::TackType::eMain);
        _trackInterface.turnOffTrack(TrackInterface::TackType::eProg);
        _trackInterface.turnOffTrack(TrackInterface::TackType::eJoin);
    }
}