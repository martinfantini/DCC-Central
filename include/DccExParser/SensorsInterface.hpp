#ifndef __DCC_EX_SENSORS_INTERFACE_HPP__
#define __DCC_EX_SENSORS_INTERFACE_HPP__

#include <string>
#include <unordered_map>

namespace DccExParser
{
    class SensorsInterface
    {
        public:
            // To count the active sensors
            virtual int countSensors() = 0;
            //To manage sensors
            virtual void addSensor(int sensorId, int virtualPin, bool isPullUp) = 0;
            virtual void removeSensor(int sensorId) = 0;
            // get information about specific sensor
            virtual bool getStatusSensor(int sensorId) = 0;
            virtual void setStatusSensor(int sensorId, bool Status) = 0;
            // returns id, status
            virtual const std::unordered_map<int, bool> getStatusSensors() = 0;
            // returns id, vpin, pullUp
            virtual const std::unordered_map<int, std::pair<int, bool>> getConfigurationSensors() = 0;

            virtual ~SensorsInterface(){}
    };
}

#endif