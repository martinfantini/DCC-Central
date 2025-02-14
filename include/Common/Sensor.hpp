#ifndef __COMMON_SENSORS_INFORMATION_HPP__
#define __COMMON_SENSORS_INFORMATION_HPP__

#include <unordered_set>

namespace Common
{
    enum SensorStatusEnum
    {
        SensorStatusEnum_None = 0,
        Busy,
        Free,
    };

    struct Sensor
    {
        int Id;
        int Pin;
        SensorStatusEnum Status = SensorStatusEnum::SensorStatusEnum_None;
    };
}

#endif
