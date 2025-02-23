#include "Mananger/SensorManager.hpp"
#include "Common/SensorCache.hpp"

#include <glog/logging.h>

namespace Central
{
    int SensorsManager::countSensors()
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        LOG(DEBUG) << "Count Sensors: " << m_SensorCache.size();
        return m_SensorCache.size();
    }

    void SensorsManager::addSensor(int sensorId, int virtualPin, bool isPullUp)
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        LOG(DEBUG) << "Insert Sensor: Id: " << sensorId << ", VirtualPin: " << virtualPin << ", isPullUp: " << std::boolalpha << isPullUp;
        m_SensorCache.Insert({.Id = sensorId, .Pin = virtualPin, .PullUp = isPullUp});
    }

    void SensorsManager::removeSensor(int sensorId)
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        LOG(DEBUG) << "Remove Sensor: Id: " << sensorId;
        m_SensorCache.RemoveById(int sensorId);
    }

    bool SensorsManager::getStatusSensor(int sensorId)
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        auto sensor = m_SensorCache.GetSensorById(sensorId);
        if (sensor->Status == SensorStatusEnum::SensorStatusEnum_None || sensor->Status == SensorStatusEnum::Free)
        {
            LOG(DEBUG) << "Free Sensor: Id: " << sensor->Id << ", Pin: " << sensor->Pin;
            return false;
        }

        LOG(DEBUG) << "Busy Sensor: Id: " << sensor->Id << ", Pin: " << sensor->Pin;
        return true;
    }

    void SensorsManager::setStatusSensor(int sensorId, bool Status)
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        auto sensor = m_SensorCache.GetSensorById(sensorId);
        if (Status)
        {
            LOG(DEBUG) << "Set Busy Sensor: Id: " << sensor->Id << ", Pin: " << sensor->Pin;
            sensor->Status == SensorStatusEnum::Busy;
        }

        LOG(DEBUG) << "Set Free Sensor: Id: " << sensor->Id << ", Pin: " << sensor->Pin;
        sensor->Status == SensorStatusEnum::Free;
    }

    void SensorsManager::setStatusPinSensor(int pin, bool Status)
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        auto sensor = m_SensorCache.GetSensorByPin(pin);
        if (Status)
        {
            LOG(DEBUG) << "Set Busy Sensor: Id: " << sensor->Id << ", Pin: " << sensor->Pin;
            sensor->Status == SensorStatusEnum::Busy;
        }
        LOG(DEBUG) << "Set Free Sensor: Id: " << sensor->Id << ", Pin: " << sensor->Pin;
        sensor->Status == SensorStatusEnum::Free;
    }

    const std::unordered_map<int, bool> SensorsManager::getStatusSensors()
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        std::unordered_map<int, bool> result;
        for(auto& sensor: m_SensorCache.SensorVector())
        {
            result.insert({sensor.Id, sensor.Status == SensorStatusEnum::Busy});
        }
        return result;
    }

    const std::unordered_map<int, std::pair<int, bool>> SensorsManager::getConfigurationSensors()
    {
        const std::lock_guard<std::mutex> lock_cache(sensor_cache_mutex);
        std::unordered_map<int, std::pair<int, bool>> result;
        for(auto& sensor: m_SensorCache.SensorVector())
        {
            result.insert({sensor.Id, {sensor.Pin, sensor.PullUp}});
        }
        return result;
    }
}
