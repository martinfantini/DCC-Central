#ifndef __CENTRAL_ACCESSORY_MANAGER_HPP__
#define __CENTRAL_ACCESSORY_MANAGER_HPP__

#include <mutex>
#include <DccExParser/SensorsInterface.hpp>
#include <Common/SensorCache.hpp>

namespace Central
{
    class SensorsManager : public DccExParser::SensorsInterface
    {
        public:

            int countSensors() override;

            void addSensor(int sensorId, int virtualPin, bool isPullUp)  override;

            void removeSensor(int sensorId) override;
            
            bool getStatusSensor(int sensorId) override;

            void setStatusSensor(int sensorId, bool Status) override;

            void setStatusPinSensor(int pin, bool Status);

            virtual const std::unordered_map<int, bool> getStatusSensors() override;

            virtual const std::unordered_map<int, std::pair<int, bool>> getConfigurationSensors() override;

        private:
            // All stored Locos
            Common::SensorCache m_SensorCache;

            // mutex to access to the map
            std::mutex sensor_cache_mutex;
    };
}

#endif
