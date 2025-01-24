#include "DccExCommadConverter.hpp"
#include "LocoInterface.hpp"
#include "Helpers.hpp"

namespace DccExParser
{
    DccExCommandParser::DccExCommandParser(CommandInterface& _command_interface, string_function& send_response, string_function& logger):
        _command_interface(_command_interface),
        _send_response(send_response),
        _logger(logger)
    {}

    void DccExCommandParser::parsed_values(const char command, const std::vector<std::string>& parameters)
    {
        std::string response;

        // here are the number of parameters, which are passed
        const auto params = parameters.size();

        switch (command)
        {
            case '\0':
                return; // filterCallback asked us to ignore

            case '0': // 0, Track power off
            {
                if (params > 1) 
                    break;
                TrackInterface& trackInterface = _command_interface.getTrackInterface();
                if (params==0) 
                {
                    trackInterface.turnOffTrack(TrackInterface::eMain);
                    trackInterface.turnOffTrack(TrackInterface::eProg);
                }
                else if (parameters[0] == "MAIN")
                {
                    trackInterface.turnOffTrack(TrackInterface::eMain);
                }
                else if (parameters[0] == "JOIN")
                {
                    trackInterface.turnOffTrack(TrackInterface::eMain);
                    trackInterface.turnOffTrack(TrackInterface::eProg);
                    trackInterface.turnOffTrack(TrackInterface::eJoin);                    
                }
                else if (parameters[0] == "PROG")
                {
                    trackInterface.turnOffTrack(TrackInterface::eProg);
                }
                else 
                {
                    break;
                }
                _send_response(Helpers::print_DccTrackStatus(trackInterface));
                return;
        	}
            case '1':  // 1, Track power on
            {
                if (params > 1) break;
                TrackInterface& trackInterface = _command_interface.getTrackInterface();
                if (params==0) 
                {
                    trackInterface.turnOnTrack(TrackInterface::eMain);
                    trackInterface.turnOnTrack(TrackInterface::eProg);
                }
                else if (parameters[0] == "MAIN")
                {
                    trackInterface.turnOnTrack(TrackInterface::eMain);
                }
                else if (parameters[0] == "JOIN")
                {
                    trackInterface.turnOnTrack(TrackInterface::eMain);
                    trackInterface.turnOnTrack(TrackInterface::eProg);
                    trackInterface.turnOnTrack(TrackInterface::eJoin);                    
                }
                else if (parameters[0] == "PROG")
                {
                    trackInterface.turnOnTrack(TrackInterface::eProg);
                }
                else 
                {
                    break;
                }
                _send_response(Helpers::print_DccTrackStatus(trackInterface));
                return;
            }
            case '!': // ESTOP ALL  <!>
            {
                TrackInterface& trackInterface = _command_interface.getTrackInterface();
                Helpers::emergencyStop(trackInterface);
                _command_interface.getLocosInfo().emergencyStop();
                _send_response("<O>\n");
                break;
            }
            case '#':
            {
                _send_response("<# " + std::to_string(_command_interface.getLocosInfo().getMaxLocos()) +">\n");
                return;
            }
            case '-': // Forget Loco <- [cab]>
            {
                if (params != 1) break;

                auto locoId = atoi(parameters[0].c_str());
                if (locoId < 0)
                    return;

                if (locoId == 0)
                {
                    _command_interface.getLocosInfo().removeAllLocos();
                    _send_response("<O>\n");
                }
                else
                {
                    _command_interface.getLocosInfo().removeLoco(locoId);
                    _send_response("<O>\n");
                }
                return;
            }
            case 'F': // New command to call the new Loco Function API <F cab func 1|0>
            {
                if (params != 3) 
                    break;

                auto locoId = atoi(parameters[0].c_str());
                auto function = atoi(parameters[1].c_str());
                auto status = atoi(parameters[2].c_str());
                _command_interface.getLocosInfo().setFunction(locoId, function, status == 1);
                break;
            }
            case 'Q': // SENSORS <Q>
            {
                _send_response(Helpers::print_DccSensorStatus(_command_interface.getSensors()));
                return;
            }
            case 's': // <s>
            {
                _send_response(Helpers::print_DccInfo(_command_interface.getInfo()));
                _send_response(Helpers::print_DccTrackStatus(_command_interface.getTrackInterface()));
                _send_response(Helpers::print_DCCTurnout(_command_interface.getTurnout()));
                _send_response(Helpers::print_DccSensorStatus(_command_interface.getSensors()));
                return;
            }
            case 'S':
            {
                switch (params)
                {
                    case 3: // <S id pin pullup>  create sensor. pullUp indicator (0=LOW/1=HIGH)
                    {
                        auto sensorId = atoi(parameters[0].c_str());
                        auto virtualPin = atoi(parameters[1].c_str());
                        auto isPullUp = atoi(parameters[2].c_str()) == 1;
                        _command_interface.getSensors().addSensor(sensorId, virtualPin, isPullUp);
                        _send_response("<O>\n");
                        return;
                    }
                    case 1:
                    {
                        auto sensorId = atoi(parameters[0].c_str());
                        _command_interface.getSensors().removeSensor(sensorId);
                        _send_response("<O>\n");
                        return;
                    }
                    case 0:
                    {
                        _send_response(Helpers::print_DCCSensorConfiguration(_command_interface.getSensors()));
                        return;
                    }
                }
                break;
            }
            case 'H':
            {
                _send_response(Helpers::print_DCCTurnout(_command_interface.getTurnout()));
                return;
            }
            case 'T':
            {
                
            }

    /*


            case 't':   // THROTTLE <t [REGISTER] CAB SPEED DIRECTION>
            {
                if (params == 1) {  // <t cab>  display state
                    int cad_id = atoi(parameters[1].c_str());
                    auto result = _manager.lookupLocos(cad_id);
                    if (result.first)
                    {
                        auto& loco = result.second;
                        char* response;
                        asprintf(&response, "<l %d %d %d %l>\n", loco.loco, loco.locoId, loco.speedCode, loco.functions);
                        _send_response(response);
                        return;
                    }
                    else // send dummy state speed 0 fwd no functions.
                    {
                        char* response;
                        asprintf(&response, "<l %d -1 128 0>\n", cad_id);
                        _send_response(response);
                    }
                }
                else if (params == 3 || params == 4)
                {
                    int regis;
                    int cab;
                    int tspeed;
                    int direction;

                    if (params == 4)  // <t REGISTER CAB SPEED DIRECTION>
                    {
                        regis = atoi(parameters[0].c_str());
                        cab = atoi(parameters[1].c_str());
                        tspeed = atoi(parameters[2].c_str());
                        direction = atoi(parameters[3].c_str());
                    }
                    else if (params == 3)
                    {
                        cab = atoi(parameters[0].c_str());
                        tspeed = atoi(parameters[1].c_str());
                        direction = atoi(parameters[2].c_str());
                    }

                    // Convert DCC-EX protocol speed steps where
                    // -1=emergency stop, 0-126 as speeds
                    // to DCC 0=stop, 1= emergency stop, 2-127 speeds
                    if (tspeed > 126 || tspeed < -1)
                        break; // invalid JMRI speed code
                    if (tspeed < 0)
                        tspeed = 1; // emergency stop DCC speed
                    else if (tspeed > 0)
                        tspeed++; // map 1-126 -> 2-127
                    if (cab == 0 && tspeed > 1)
                        break; // ignore broadcasts of speed>1
                    if (direction < 0 || direction > 1)
                        break; // invalid direction code
	                if (cab > 10239 || cab < 0)
	                    break; // beyond DCC range

                    _manager.setThrottle(cab, tspeed, direction);

                    if (params == 4) // send obsolete format T response
                    {
                        char* response;
                        asprintf(&response, "<T %d %d %d>\n", regis, tspeed, direction);
                        _send_response(response);
                    }
                }
            }
            case 'f': // FUNCTION <f CAB BYTE1 [BYTE2]>
            {
                if (parse_f(params, parameters))
                    return;
                break;
            }*/
           
        }

        // Send default response
        _send_response("<X>\n");
    }

    bool DccExCommandParser::funcmap(int16_t cab, char value, int fstart, int fstop)
    {
        /*for (int16_t i = fstart; i <= fstop; i++)
        {
            if (! _manager.setFunction(cab, i, value & 1)) return false;
            value >>= 1;
        }*/
        return true;
    }

    bool DccExCommandParser::parse_f(int params, const std::vector<std::string>& parameters)
    {
        // JMRI sends this info in DCC message format but it's not exactly
        // convenient for other processing
        if (params < 2)
            return false;

        int cab = atoi(parameters[0].c_str());
        // convert string to hex
        char param_1 = std::stoi(parameters[1], 0, 16);

        if (params == 2)
        {
            char instructionField = param_1 & 0xE0;   // 1110 0000
            if (instructionField == 0x80)
            {
                // 1000 0000 Function group 1
                // Shuffle bits from order F0 F4 F3 F2 F1 to F4 F3 F2 F1 F0
                char normalized = (param_1 << 1 & 0x1e) | (param_1 >> 4 & 0x01);
                return (funcmap(cab, normalized, 0, 4));
            }
            else if (instructionField == 0xA0)
            {
                // 1010 0000 Function group 2
                if (param_1 & 0x10)
                {
                    // 0001 0000 Bit selects F5toF8 / F9toF12
	                return (funcmap(cab, param_1, 5, 8));
                }
                else
                {
                    return (funcmap(cab, param_1, 9, 12));
                }
	        }
        }
        else if (params == 3)
        {
            char param_2 = std::stoi(parameters[2], 0, 16);
            if (param_1 == 0xDE)
            {
                return (funcmap(cab, param_2, 13, 20));
            }
            else if (param_1 == 0xDF)
            {
                return (funcmap(cab, param_2, 21, 28));
            }
        }
        return false;
    }
}
