#ifndef __COMMON_SENSORS_INFORMATION_HPP__
#define __COMMON_SENSORS_INFORMATION_HPP__

#include <unordered_map>

namespace Common::SensorInformation
{
    enum StatusInformation
    {
        None = 0,
        Busy,
        Free,
    };

    struct Sensor
    {
        StatusInformation StatusInformation = StatusInformation::None;
    };

    // This map stores VirtualPin and Sensor
    typedef std::unordered_map<int, Sensor> sensor_map_type;
    sensor_map_type SensorMap;
}

#endif