
#include "DccCommandGenerator.hpp"
#include "DccConstants.hpp"

namespace DccProtocol
{
    using namespace DccProtocol::DccConstants;

    bool DccCommandGenerator::CalculateCheckSum(std::vector<char>& instruction)
    {
        if (instruction.size() > MAX_PACKET_SIZE || instruction.size() == 0) 
            return false;

        char checksum = 0;
        for (auto value: instruction)
            checksum ^= value;

        instruction.push_back(checksum);

        return true;
    }

    void DccCommandGenerator::AddressEncoding(int cab, std::vector<char>& instruction)
    {
        if (cab > HIGHEST_SHORT_ADDR)
            instruction.push_back(HighByte(cab) | 0xC0);
        instruction.push_back(LowByte(cab));
    }

    char DccCommandGenerator::HighByte(int cab)
    {
        return static_cast<char>((cab >> 8) & 0xFF);
    }

    char DccCommandGenerator::LowByte(int cab)
    {
        return static_cast<char>(cab & 0xFF);
    }

    void DccCommandGenerator::SetLocoSpeedDirection(int cab, int Speed, bool Direction, int SpeedSteps)
    {
        std::vector<char> instruction;
        AddressEncoding(cab, instruction);

        int _SpeedSteps = getGlobalSpeedSteps();
        if (SpeedSteps != 0)
        {
            _SpeedSteps = SpeedSteps;
        }

        char SpeedCode = (Speed & 0x7F) + (Direction ? 1 : 0) * 128;

        // For the 128 Steps.
        if (_SpeedSteps >= 128)
        {
            // 128-step speed control byte
            instruction.push_back(SET_SPEED);
            instruction.push_back(SpeedCode);
        }
        // For the 28 Steps.
        else
        {

            char Speed128 = SpeedCode & 0x7F;
            char Speed28;
            char Code28;

            if (Speed128 == 0 || Speed128 == 1)
            {
                Code28 = Speed128; // stop or emergency stop
            }
            else
            {
                Speed28= (Speed128 * 10 + 36) / 46;  // convert 2-127 to 1-28
                Code28 = (Speed28 + 3) / 2 | ((Speed28 & 1) ? 0 : 0b00010000 ); // convert 1-28 to DCC 28 step speed code
            }
            //                  Construct command byte from:
            //                command     speed       direction
            instruction.push_back(0b01000000 | Code28 | ((SpeedCode & 0x80) ? 0b00100000 : 0));
        }
        SendInternalDCC(instruction);
    }

    void DccCommandGenerator::SetFunctionInternal(int cab, char byte1, char byte2)
    {
        std::vector<char> instruction;
        AddressEncoding(cab, instruction);
        if (byte1 != 0x00)
        {
            instruction.push_back(byte1);
        }
        instruction.push_back(byte2);
        SendInternalDCC(instruction);
    }

    void DccCommandGenerator::SetLocoAnalogFunction(int cab, int AnalogFunction, int AnalogData)
    {
        if (AnalogFunction < 0 || AnalogFunction > 255)
            return;
    
        if (AnalogData < 0 || AnalogData > 255)
            return;

        std::vector<char> instruction;
        AddressEncoding(cab, instruction);
        instruction.push_back(0x3D);
        instruction.push_back(static_cast<char>(AnalogFunction));
        instruction.push_back(static_cast<char>(AnalogData));
        SendInternalDCC(instruction);
    }

    void DccCommandGenerator::SendInternalDCC(std::vector<char>& instruction, int RepeatCommand, bool DeliverAnAnswer)
    {
        // Generate the checksum
        CalculateCheckSum(instruction);
        // Send the instruction
        _DccInterface.SendToDCC(instruction, RepeatCommand, DeliverAnAnswer);
    }

    /*void DccCommandGenerator::SetDataCommand()
    {
        std::vector<char> instruction;
        instruction.push_back(0x00);

        SendInternalDCC(instruction);
    }*/

    void DccCommandGenerator::SetTimeCommand(int hour, int minutes, int weekOfDay, int accelerationFactor, bool Update)
    {
        if (hour < 0 || hour > 23)
            return;

        if (minutes < 0 || minutes > 59)
            return;

        if (weekOfDay < 0 || weekOfDay > 6)
            return;

        if (accelerationFactor < 0 || accelerationFactor > 63)
            return;

        std::vector<char> instruction;
        //Broadcast instruction
        instruction.push_back(0x00);
        instruction.push_back(0xC1);
        //                     00    MMMMMM
        instruction.push_back(0x3F | minutes);
        //                           WWW                    HHHHH                          
        instruction.push_back((weekOfDay << 5 | 0x70) | (hour | 0x1F));
        //                              U0                   BBBBBB
        instruction.push_back( (Update ? 0x80: 0x00) | (0x1F | accelerationFactor));
        SendInternalDCC(instruction);
    }

    void DccCommandGenerator::SetEmergencyStrop(int cab)
    {
        SetLocoSpeedDirection(cab, 1, 1);
    }

    void DccCommandGenerator::SetTimeCommand(int dayInMonth, int month, int year)
    {
        if (dayInMonth < 1 || dayInMonth > 31)
            return;

        if (month < 1 || month > 12)
            return;

        if (year < 0 || year > 4096)
            return;
        
        std::vector<char> instruction;
        //Broadcast instruction
        instruction.push_back(0x00);
        instruction.push_back(0xC1);
        // 010TTTTT
        instruction.push_back(0x5F | dayInMonth | 0x1F);
        //                                     MMMM        YYYY
        instruction.push_back(((month << 4) | 0xF0) | ((year & 0x0F00) >> 16));
        // YYYYYYYY
        instruction.push_back(year & 0xFF);
        SendInternalDCC(instruction);
    }

    void DccCommandGenerator::SetAccessory(int address, int port, bool gate, bool onoff)
    {
        if (address < 0 && address > 511)
            return;

        if (port < 0 && port > 3)
            return;

        std::vector<char> instruction;
        instruction.push_back(address % 64 + 128);
        char accessory_instruction = ((((address / 64) % 8) << 4) + (port % 4 << 1) + gate % 2) ^ 0xF8;
        if (!onoff)
        {
            accessory_instruction &= ~0x08; // set C to 0
        }
        instruction.push_back(accessory_instruction);
        SendInternalDCC(instruction, 3);
    }

    void DccCommandGenerator::SetLocoFunction(int cab, int function, bool status)
    {


    }

    void DccCommandGenerator::SetFunction_F1_F4(int number, bool status, std::vector<char>& instruction)
    {}

    void DccCommandGenerator::SetFunction_F5_F12(int number, bool status, std::vector<char>& instruction)
    {}

    void DccCommandGenerator::SetFunction_F13_F20(int number, bool status, std::vector<char>& instruction)
    {}

    void DccCommandGenerator::SetFunction_F21_F28(int number, bool status, std::vector<char>& instruction)
    {}
}