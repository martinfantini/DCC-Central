#include "DccExCommandConverter.hpp"
#include "LocoInterface.hpp"
#include "Helpers.hpp"

using namespace DccExParser;
using namespace Helpers;
namespace
{
    bool funcmap(int16_t cab, char value, int fstart, int fstop, LocoInterface& _locoInterface)
    {
        for (int16_t i = fstart; i <= fstop; i++)
        {
            if (!_locoInterface.setFunction(cab, i, value & 1))
                return false;
            value >>= 1;
        }
        return true;
    }

    bool parse_f(int params, const std::vector<std::string>& parameters, LocoInterface& _locoInterface)
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
                return (funcmap(cab, normalized, 0, 4, _locoInterface));
            }
            else if (instructionField == 0xA0)
            {
                // 1010 0000 Function group 2
                if (param_1 & 0x10)
                {
                    // 0001 0000 Bit selects F5toF8 / F9toF12
	                return (funcmap(cab, param_1, 5, 8, _locoInterface));
                }
                else
                {
                    return (funcmap(cab, param_1, 9, 12, _locoInterface));
                }
	        }
        }
        else if (params == 3)
        {
            char param_2 = std::stoi(parameters[2], 0, 16);
            if (param_1 == 0xDE)
            {
                return (funcmap(cab, param_2, 13, 20, _locoInterface));
            }
            else if (param_1 == 0xDF)
            {
                return (funcmap(cab, param_2, 21, 28, _locoInterface));
            }
        }
        return false;
    }
}

namespace DccExParser
{
    DccExCommandParser::DccExCommandParser(CommandInterface& _command_interface, string_function_type& send_response):
        _command_interface(_command_interface),
        _send_response(send_response)
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
                _send_response(Helpers::print_DCC_Track_Status(trackInterface));
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
                _send_response(Helpers::print_DCC_Track_Status(trackInterface));
                return;
            }
            case '!': // ESTOP ALL  <!>
            {
                TrackInterface& trackInterface = _command_interface.getTrackInterface();
                Helpers::emergencyStop(trackInterface);
                _command_interface.getLocosInterface().emergencyStop();
                _send_response("<O>\n");
                break;
            }
            case '#':
            {
                _send_response("<# " + std::to_string(_command_interface.getLocosInterface().getMaxLocos()) +">\n");
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
                    _command_interface.getLocosInterface().removeAllLocos();
                    _send_response("<O>\n");
                }
                else
                {
                    _command_interface.getLocosInterface().removeLoco(locoId);
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
                _command_interface.getLocosInterface().setFunction(locoId, function, status == 1);
                break;
            }
            case 'Q': // SENSORS <Q>
            {
                _send_response(Helpers::print_DCC_Sensor_Status(_command_interface.getSensorsInterface()));
                return;
            }
            case 's': // <s>
            {
                _send_response(Helpers::print_DCC_Info(_command_interface.getInfoInterface()));
                _send_response(Helpers::print_DCC_Track_Status(_command_interface.getTrackInterface()));
                _send_response(Helpers::print_DCC_Turnout(_command_interface.getTurnoutInterface()));
                _send_response(Helpers::print_DCC_Sensor_Status(_command_interface.getSensorsInterface()));
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
                        _command_interface.getSensorsInterface().addSensor(sensorId, virtualPin, isPullUp);
                        _send_response("<O>\n");
                        return;
                    }
                    case 1:
                    {
                        auto sensorId = atoi(parameters[0].c_str());
                        _command_interface.getSensorsInterface().removeSensor(sensorId);
                        _send_response("<O>\n");
                        return;
                    }
                    case 0:
                    {
                        _send_response(Helpers::print_DCC_Sensor_Configuration(_command_interface.getSensorsInterface()));
                        return;
                    }
                }
                break;
            }
            case 'H':
            {
                _send_response(Helpers::print_DCC_Turnout(_command_interface.getTurnoutInterface()));
                return;
            }
            case 'T':
            {
                switch (params)
                {
                    case 0: // <T>  list turnout definitions
                    {
                        _send_response(Helpers::print_DCC_Turnout(_command_interface.getTurnoutInterface()));
                        return;
                    }
                    case 1: // <T id>  delete turnout
                    {
                        int turnoutId = atoi(parameters[0].c_str());
                        _command_interface.getTurnoutInterface().removeTurnout(turnoutId);
                        _send_response("<O>\n");
                        return;
                    }
                    case 2: // <T id 0|1|T|C>
                    {
                        int turnoutId = atoi(parameters[0].c_str());
                        char status = parameters[1].at(0);
                        bool _stateClose = false;
                        switch(status)
                        {
                            case '0':
                            case 'T':
                                _stateClose = true;
                            case '1':
                            case 'C':
                                _stateClose = false;
                        }
                        _command_interface.getTurnoutInterface().statusTurnoutClose(turnoutId, _stateClose);
                        return;
                    }
                    default:
                    {
                        if ((params > 2) && parameters[1] == "DCC") // <T id DCC n m> or <T id DCC nn>
                        {
                            int turnoutId = atoi(parameters[0].c_str());
                            int address = atoi(parameters[2].c_str());
                            if(params==4)
                            {
                                int subAddress = atoi(parameters[3].c_str());
                                _command_interface.getTurnoutInterface().createTurnout(turnoutId, address, subAddress);
                            }
                            else
                            {
                                _command_interface.getTurnoutInterface().createTurnout(turnoutId, address);
                            }
                            return;
                        }
                    }
                }
            }
            case 'a': // ACCESSORY <a ADDRESS SUBADDRESS ACTIVATE [ONOFF]> or <a LINEARADDRESS ACTIVATE>
            {
                if (params < 2)
                    break;

                int _address = atoi(parameters[0].c_str());
                switch (params)
                {
                    case 2: // <a LINEARADDRESS ACTIVATE>
                    {
                        bool _activate = atoi(parameters[1].c_str()) == 1;
                        _command_interface.getAccessoryInterface().setAccessory(_address, _activate);
                    }
                    case 3: // // <a ADDRESS SUBADDRESS ACTIVATE>
                    {
                        int _subAddress = atoi(parameters[1].c_str());
                        bool _activate = atoi(parameters[2].c_str()) == 1;
                        _command_interface.getAccessoryInterface().setAccessory(_address, _subAddress, _activate);
                    }
                    case 4: // <a ADDRESS SUBADDRESS ACTIVATE [ONOFF]>
                    {
                        int _subAddress = atoi(parameters[1].c_str());
                        bool _activate = atoi(parameters[2].c_str()) == 1;
                        bool _onOff = atoi(parameters[2].c_str()) == 1;
                        _command_interface.getAccessoryInterface().setAccessory(_address, _subAddress, _activate, _onOff);
                    }
                }
                return;
            }
            case 't': // <t [REGISTER] CAB SPEED DIRECTION>
            {
                if (params < 1) break;

                int _cab = atoi(parameters[0].c_str());
                int _locoId;
                int _tspeed;
                bool _direction;

                switch (params)
                {
                    case 1: // <t cab>  display state
                    {
                        long _functions;
                        if (!_command_interface.getLocosInterface().getLoco(_cab, _locoId, _tspeed, _functions))
                        {
                            _locoId = -1;
                            _tspeed = 128;
                            _functions = 0;
                        }
                        _send_response(Helpers::print_DCC_Loco_Info(_cab, _locoId, _tspeed, _functions));
                        return;
                    }
                    case 4: // <t REGISTER CAB SPEED DIRECTION>
                    {
                        _cab = atoi(parameters[1].c_str());
                        _tspeed = atoi(parameters[2].c_str());
                        _direction = atoi(parameters[3].c_str()) == 1;
                        if (!_command_interface.getLocosInterface().setLoco(_cab, _tspeed, _direction));
                            break;
                        _send_response(Helpers::print_DCC_Loco_Status(parameters));
                        return;
                    }
                    case 3: // <t CAB SPEED DIRECTION>
                    {
                        _cab = atoi(parameters[0].c_str());
                        _tspeed = atoi(parameters[1].c_str());
                        _direction = atoi(parameters[2].c_str()) == 1;
                        if ( !_command_interface.getLocosInterface().setLoco(_cab, _tspeed, _direction));
                            break;
                        return;
                    }
                }
                break;
            }
            case 'f':
            {
                parse_f(params, parameters, _command_interface.getLocosInterface());
                break;
            }
            case 'c':
            {
                _send_response(Helpers::print_DCC_Current_On_Main(_command_interface.getDccTrackInterface()));
                return;
            }
            case 'J':
            {
                if ((params<1) | (params>3)) // <J> 
                    break;

                switch (parameters[0].at(0))
                {
                    case 'I':
                    {
                        _send_response(Helpers::print_Throttle_DCC_Current(_command_interface.getDccTrackInterface()));
                        return;
                    }
                    case 'T':
                    {
                        if (params == 1) // <JT>
                        {
                            _send_response(Helpers::print_Throttle_DCC_Turnout_List(_command_interface.getTurnoutInterface()));
                            return;
                        }
                        else if (params == 2) // <JT id>
                        {
                            int _turnoutId = atoi(parameters[1].c_str());
                            _send_response(Helpers::print_Throttle_DCC_Turnout_Info(_turnoutId, _command_interface.getTurnoutInterface()));
                            return;
                        }
                        return;
                    }
                }
                break;
            }
            case 'M': // WRITE TRANSPARENT DCC PACKET MAIN <M REG X1 ... X9>
            {
                if (params < 1)
                    return;

                std::vector<char> values;
                // drop REG
                for (int pos = 1; pos < params; pos++)
                    values.push_back(parameters[pos].at(0));
                _command_interface.getDccTrackInterface().writeByteOnMain(values);
                return;
            }
            case 'P': // WRITE TRANSPARENT DCC PACKET PROG <P REG X1 ... X9>
            {
                if (params < 1)
                    return;

                std::vector<char> values;
                // drop REG
                for (int pos = 1; pos < params; pos++)
                    values.push_back(parameters[pos].at(0));
                _command_interface.getDccTrackInterface().writeByteOnProg(values);
                return;
            }
            case 'W': // WRITE CV ON PROG <W CV VALUE CALLBACKNUM CALLBACKSUB>
            {
                if (params < 1)
                    return;

                int _cv = atoi(parameters[0].c_str());

                if (params == 1)
                {  // <W id> Write new loco id (clearing consist and managing short/long)
                    auto _result = _command_interface.getDccTrackInterface().setLocoId(_cv);
                    _send_response(print_DCC_Write_LocoId(_result, parameters));
                    return;
                }

                if (params < 2)
                    return;

                int _value = atoi(parameters[1].c_str());

                if (params == 4)
                { // <W CV VALUE [CALLBACKNUM] [CALLBACKSUB]>
                    auto _result = _command_interface.getDccTrackInterface().writeCVByte(_cv, _value);
                    _send_response(print_DCC_Write_write_CV_Byte_4(_result, parameters));
                }
                else
                { // <W CV VALUE>
                    auto _result = _command_interface.getDccTrackInterface().writeCVByte(_cv, _value);
                    _send_response(print_DCC_Write_write_CV_Byte(_result, parameters));
                }
                return;
            }
            case 'V': // VERIFY CV ON PROG <V CV VALUE> <V CV BIT 0|1>
            {
                if (params == 2)
                {  // <V CV VALUE>
                    int _cv = atoi(parameters[0].c_str());
                    char _value = parameters[1].at(0);

                    auto _result = _command_interface.getDccTrackInterface().verifyCVByte(_cv, _value);
                    _send_response(print_DCC_Read_Byte(_result, parameters));
                    return;
                }
                if (params == 3)
                { // <V CV BIT 0|1>
                    if (params < 3) return;

                    int _cv = atoi(parameters[0].c_str());
                    int _position = atoi(parameters[1].c_str());
                    bool _value = atoi(parameters[2].c_str()) == 1;

                    auto _result = _command_interface.getDccTrackInterface().verifyCVBit(_cv, _position, _value);
                    _send_response(print_DCC_Read_Bit(_result, parameters));
                    return;
                }
                break;
            }
            case 'B': // WRITE CV BIT ON PROG <B CV BIT VALUE CALLBACKNUM CALLBACKSUB>
            {
                if (params < 3) return;

                int _cv = atoi(parameters[0].c_str());
                int _position = atoi(parameters[1].c_str());
                bool _value = (atoi(parameters[2].c_str())) == 1;
                auto _result = _command_interface.getDccTrackInterface().writeCVBit(_cv, _position, _value);

                _send_response(print_DCC_Write_Bit(_result, parameters));
                return;
            }
            case 'R': // READ CV ON PROG
            {
                if (params == 0)
                { // <R> New read loco id
                    auto _result = _command_interface.getDccTrackInterface().getLocoId();
                    _send_response(print_DCC_Read_LocoId(_result));
                    return;
                }

                if (params < 1)
                    return;

                int _cv = atoi(parameters[0].c_str());

                if (params == 1)
                { // <R CV> -- uses verify callback
                    auto _result = _command_interface.getDccTrackInterface().verifyCVByte(_cv, 0);
                    _send_response(print_DCC_Read_Byte(_result, parameters));
                    return;
                }
                if (params == 3)
                { // <R CV CALLBACKNUM CALLBACKSUB>
                    auto _result = _command_interface.getDccTrackInterface().readCV(_cv);
                    _send_response(print_DCC_Read_CV(_result, parameters));
                    return;
                }
                break;
            }
            case 'w': // WRITE CV on MAIN <w CAB CV VALUE>
            {
                if (params < 3) return;

                int _cab = atoi(parameters[0].c_str());
                int _cv = atoi(parameters[1].c_str());
                char _value = parameters[2].at(0);
                _command_interface.getDccTrackInterface().writeCVByteMain(_cab, _cv, _value);
                return;
            }
            case 'b': // WRITE CV BIT ON MAIN <b CAB CV BIT VALUE>
            {
                if (params < 4) return;

                int _cab = atoi(parameters[0].c_str());
                int _cv = atoi(parameters[1].c_str());
                int _position = atoi(parameters[2].c_str());
                bool _value = (atoi(parameters[2].c_str())) == 1;
                _command_interface.getDccTrackInterface().writeCVBitMain(_cab, _cv, _position, _value);
                return;
            }
        }

        // Send default response
        _send_response("<X>\n");
    }
}
