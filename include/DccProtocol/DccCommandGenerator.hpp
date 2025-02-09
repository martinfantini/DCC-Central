#ifndef __DCC_PROTOCOL_DCC_COMMAND_GENERATOR_HPP__
#define __DCC_PROTOCOL_DCC_COMMAND_GENERATOR_HPP__

#include <vector>

#include "DccInterface.hpp"

namespace DccProtocol
{
    /**
     * @brief This class generate all the corresponding data to be send in the wire,
     * with the different commands available in the dcc protocol specification.
     */
    class DccCommandGenerator
    {
    public:
        DccCommandGenerator(DccInterface& DccInterface):
            m_DccInterface(DccInterface)
        {}

        void GlobalSpeedSteps(int globalSpeedsteps)
        {
            m_globalSpeedsteps = globalSpeedsteps;
        }

        /**
         * @brief To set the speed and direction of a loco.
         *
         * @param cab address of the loco
         * @param Speed the speed to set in the loco.
         * @param Direction direction to set. true forward, false backwards
         * @param SpeedSteps to set the speed steps for a specific loco.
         *      In the case it is 0, it will take the GlobalSpeedSteps.
         */
        void SetLocoSpeedDirection(int cab, int Speed, bool Direction, int SpeedSteps = 0);

        /**
         * @brief Set the Loco Analog Function object
         *
         * @param cab
         * @param function
         * @param data
         */
        void SetLocoAnalogFunction(int cab, int function, int data);

        /**
         * @brief Set the Loco Function object
         *
         * @param cab
         * @param function
         * @param status
         */
        void SetLocoFunction(int cab, int function, bool status, std::vector<unsigned char>& status_vector);

        /**
         * @brief To set direct the values in the Loco
         *
         * @param cab
         * @param byte1
         * @param byte2
         */
        void SetFunctionInternal(int cab, char byte1 = 0x00, char byte2 = 0x00);

        /**
         * @brief Set the Data Command object
         *
         */
        void SetTimeCommand(int hour, int minutes, int weekOfDay, int accelerationFactor = 1, bool Update = false);

        /**
         * @brief Set the Time Command object
         *
         */
        void SetTimeYearCommand(int dayInMonth, int month, int year);

        /**
         * @brief Set the Emergency Strop object
         *
         * @param cab
         */
        void SetEmergencyStrop(int cab = 0);

        /**
         * @brief Set the Accessory object
         *
         * @param address
         * @param port
         * @param gate
         * @param onoff
         */
        void SetAccessory(int address, int port, bool gate, bool onoff);

#ifndef UNIT_TEST_PRIVATE_METHODS
    private:
#endif

        bool CalculateCheckSum(std::vector<unsigned char>& instructions);
        void AddressEncoding(int cab, std::vector<unsigned char>& instructions);
        unsigned char HighByte(int cab);
        unsigned char LowByte(int cab);
        void SendInternalDCC(std::vector<unsigned char>& instructions, int RepeatCommand = 0);

        int getGlobalSpeedSteps() const
        {
            return m_globalSpeedsteps;
        }

        void SetFunction_F1_F4(int number, bool status, std::vector<unsigned char>& instruction, unsigned char& _status_F1_F4);
        void SetFunction_F5_F12(int number, bool status, std::vector<unsigned char>& instruction, unsigned char& _status_F5_F12);
        void SetFunction_F13_F20(int number, bool status, std::vector<unsigned char>& instruction, unsigned char& _status_F13_F20);
        void SetFunction_F21_F28(int number, bool status, std::vector<unsigned char>& instruction, unsigned char& _status_F21_F28);

        // Internal variables.
        DccInterface& m_DccInterface;

        // to set the global variable loco steps
        int m_globalSpeedsteps = 128;
    };
}

#endif