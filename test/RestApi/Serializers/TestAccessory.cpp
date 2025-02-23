#include <catch2/catch_test_macros.hpp>
#include <Serializers/Accessory.hpp>

using namespace RestApi::Serializer;
using namespace Common;

TEST_CASE("Accessory to json","[Accessory_ToJson]")
{
    int Address = 10;
    int SubAddress = 8;
    bool isActive = true;
    bool isOn = true;

    Accessory accessory = {.Address = Address, .SubAddress = SubAddress, .isActive=isActive, .isOn = isOn};
    auto resultObject = ToJson(accessory);

    CHECK(resultObject.at("Address").as_int64() == Address);
    CHECK(resultObject.at("SubAddress").as_int64() == SubAddress);
    CHECK(resultObject.at("IsActive").as_bool() == isActive);
    CHECK(resultObject.at("IsOn").as_bool() == isOn);
}

TEST_CASE("Accessory From json","[Accessory_FromJson]")
{
    boost::json::object dataAccessory;

    int Address = 10;
    int SubAddress = 8;
    bool isActive = true;
    bool isOn = true;

    dataAccessory["Address"] = Address;
    dataAccessory["SubAddress"] = SubAddress;
    dataAccessory["IsActive"] = isActive;
    dataAccessory["IsOn"] = isOn;

    Accessory resultAccessory = FromJson(dataAccessory);

    CHECK(resultAccessory.Address == Address);
    CHECK(resultAccessory.SubAddress == SubAddress);
    CHECK(resultAccessory.isActive == isActive);
    CHECK(resultAccessory.isOn == isOn);
}
