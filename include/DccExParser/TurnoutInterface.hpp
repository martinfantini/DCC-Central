#ifndef __DCC_EX_TURNOUT_INTERFACE_HPP__
#define __DCC_EX_TURNOUT_INTERFACE_HPP__

namespace DccExParser
{
    class TurnoutInterface
    {
        public:
            // Remove the Turnout
            virtual void removeTurnout(int sensorId) = 0;
            // The status od this map is Throw, for all sensors
            // Status: 1: Close 0: Throw
            virtual const std::unordered_map<int, bool> getTurnoutSensors() = 0;

            virtual void statusTurnoutClose(int sensorId, bool state) = 0;
            // Status: 0: Close 1: Throw
            virtual void statusTurnoutThrow(int sensorId, bool state) = 0;
            //
            virtual void createTurnout(int sensorId, int address, int subAddress) = 0;
            //
            virtual void createTurnout(int sensorId, int address) = 0;

            virtual ~TurnoutInterface(){}
    };
}

#endif