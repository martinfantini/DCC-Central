#include "Serializers/Sensor.hpp"

#include <map>
#include <string>

namespace RestApi::Serializer
{
    using namespace Common;

    boost::json::object ToJson(const Sensor& sensor)
    {
        boost::json::object obj;
        obj["Id"] = sensor.Id;
        obj["Pin"] = sensor.Pin;

        {
            std::map<SensorStatusEnum, std::string> helper_map
            {
                {SensorStatusEnum::SensorStatusEnum_None  ,"None"},
                {SensorStatusEnum::Busy ,"Busy"},
                {SensorStatusEnum::Free ,"Free"},
            };

            auto found = helper_map.find(sensor.Status);
            if (found != helper_map.end())
            {
                obj["Status"] = (*found).second;
            }
            else
            {
                obj["Status"] = "None";
            }
        }
        return obj;
    }

    Sensor FromJson(const boost::json::object &obj)
    {
        Sensor sensor;
        sensor.Id = obj.at("Id").as_int64();
        sensor.Pin = obj.at("Id").as_int64();

        {
            std::map<std::string, SensorStatusEnum> helper_map
            {
                {"None",  SensorStatusEnum::SensorStatusEnum_None},
                {"Close", SensorStatusEnum::Busy},
                {"Throw", SensorStatusEnum::Free},
            };

            auto found = helper_map.find(std::string(obj.at("Status").as_string().c_str()));
            if (found != helper_map.end())
            {
                sensor.Status = (*found).second;
            }
            else
            {
                sensor.Status = SensorStatusEnum::SensorStatusEnum_None;
            }
        }
        return sensor;
    }
}

