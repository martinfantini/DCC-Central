#include "Serializers/Accessory.hpp"

namespace RestApi::Serializer
{
    using namespace Common;

    boost::json::object ToJson(const Accessory &accessory)
    {
        boost::json::object obj;
        obj["Address"] = accessory.Address;
        obj["SubAddress"] = accessory.SubAddress;
        obj["IsActive"] = accessory.isActive;
        obj["IsOn"] = accessory.isOn;
        return obj;
    }

    Accessory FromJson(const boost::json::object &obj)
    {
        Accessory Accessory;
        Accessory.Address = obj.at("Address").as_int64();
        Accessory.SubAddress = obj.at("SubAddress").as_int64();
        Accessory.isActive = obj.at("IsActive").as_bool();
        Accessory.isOn = obj.at("IsOn").as_bool();

        return Accessory;
    }
}
