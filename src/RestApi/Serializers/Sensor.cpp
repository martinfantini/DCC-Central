#include "Serializers/Sensor.hpp"

#include <map>
#include <string>

namespace RestApi::Serializer
{
    using namespace Common;

    boost::json::object SensorSerializer::ToJson(const Common::Sensor& sensor)
    {
        boost::json::object obj;
        obj["Id"] = sensor.Id;
        obj["Pin"] = sensor.Pin;
        obj["PullUp"] = sensor.PullUp;

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

    Common::Sensor SensorSerializer::FromJson(const boost::json::object &obj)
    {
        Common::Sensor sensor;
        sensor.Id = obj.at("Id").as_int64();
        sensor.Pin = obj.at("Pin").as_int64();
        sensor.PullUp = obj.at("PullUp").as_bool();

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

