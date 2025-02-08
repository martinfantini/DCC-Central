#ifndef __COMMON_SENSORS_INFORMATION_HPP__
#define __COMMON_SENSORS_INFORMATION_HPP__

namespace Common::SensorInformation
{
    enum StatusInformation
    {
        None = 0,
        Busy,
        Free,
    };

    class Sensor
    {
        int VirtualPin;
        StatusInformation StatusInformation = StatusInformation::None;
    };

    typedef std::unordered_map<VirtualPin, Sensor> sensor_map_type;
    sensor_map_type SensorMap;
}

#endif