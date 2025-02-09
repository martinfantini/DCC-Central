#ifndef __COMMON_SENSORS_INFORMATION_HPP__
#define __COMMON_SENSORS_INFORMATION_HPP__

#include <unordered_set>

namespace Common::SensorInformation
{
    enum StatusStatusEnum
    {
        None = 0,
        Busy,
        Free,
    };

    struct Sensor
    {
        int Pin;
        StatusStatusEnum StatusStatus = StatusStatusEnum::None;

        bool operator==(const Sensor &other) const
        {
            return (this->Pin == other.Pin);
        }
    };

    struct KeyHasherSensor
    { 
        std::size_t operator()(const Sensor& key) const
        {
            return std::hash<int>()(key.Pin);
        }
    };

    typedef std::unordered_set<Sensor, KeyHasherSensor> sensor_set_type;
}

#endif
