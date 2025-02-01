#ifndef __DCC_EX_HELPERS_HPP__
#define __DCC_EX_HELPERS_HPP__

#include "TrackInterface.hpp"
#include "InfoInterface.hpp"
#include "SensorsInterface.hpp"
#include "TurnoutInterface.hpp"
#include "DccTrackInterface.hpp"

#include <string>

namespace DccExParser::Helpers
{
    // printers functions for dcc
    std::string print_DCC_Track_Status(DccExParser::TrackInterface& _trackInterface);
    std::string print_DCC_Sensor_Status(DccExParser::SensorsInterface& _sensors);
    std::string print_DCC_Sensor_Configuration(DccExParser::SensorsInterface& _sensors);
    std::string print_DCC_Info(DccExParser::InfoInterface& _info);
    std::string print_DCC_Turnout(DccExParser::TurnoutInterface& _turnout);
    std::string print_DCC_Loco_Info(int cab, int locoId ,int tspeed, long functions);

    // printers obsolete current
    std::string print_DCC_Current_On_Main(DccExParser::DccTrackInterface& _dccTruck);
    // printers Throttle helpers
    std::string print_Throttle_DCC_Current(DccExParser::DccTrackInterface& _dccTruck);
    std::string print_Throttle_DCC_Turnout_List(DccExParser::TurnoutInterface& _turnout);
    std::string print_Throttle_DCC_Turnout_Info(int _turnoutId, DccExParser::TurnoutInterface& _turnout);
    std::string print_DCC_Loco_Status(const std::vector<std::string>& parameters);

    // printers DCC readers
    std::string print_DCC_Read_CV(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Read_Byte(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Read_Bit(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Write_Bit(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Write_LocoId(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Write_write_CV_Byte_4(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Write_write_CV_Byte(int result_dcc_Data, const std::vector<std::string>& parameters);
    std::string print_DCC_Read_LocoId(int result_dcc_Data);

    // To generate the emergency stop.
    void emergencyStop(DccExParser::TrackInterface& _trackInterface);
}

#endif
