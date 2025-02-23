#include "Serializers/Accessory.hpp"

namespace RestApi::Serializer
{
    boost::json::object ToJson(const Common::Accessory &accessory)
    {
        boost::json::object obj;
        obj["Address"] = accessory.Address;
        obj["SubAddress"] = accessory.SubAddress;
        obj["IsActive"] = accessory.isActive;
        obj["IsOn"] = accessory.isOn;
        return obj;
    }

    Common::Accessory FromJson(const boost::json::object &obj)
    {
        Common::Accessory Accessory;
        Accessory.Address = obj.at("Address").as_int64();
        Accessory.SubAddress = obj.at("SubAddress").as_int64();
        Accessory.isActive = obj.at("IsActive").as_bool();
        Accessory.isOn = obj.at("IsOn").as_bool();

        return Accessory;
    }
}
