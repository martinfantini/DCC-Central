#include <catch2/catch_test_macros.hpp>

#include "Sensor.hpp"

TEST_CASE("Test Sensor Set")
{
    using namespace Common::SensorInformation;
    sensor_set_type SensorSet;

    {
        Sensor value = {.Pin=123, .StatusStatus=StatusStatusEnum::Busy};
        SensorSet.emplace(value);
    }

    {
        Sensor value = {.Pin=128, .StatusStatus=StatusStatusEnum::Free};
        SensorSet.emplace(value);
    }

    {
        Sensor value = {.Pin=125, .StatusStatus=StatusStatusEnum::Free};
        SensorSet.emplace(value);
    }

    SECTION("Test Search by Pin")
    {
        auto found = SensorSet.find({.Pin=123});
        REQUIRE(found != SensorSet.end());
        REQUIRE(found->StatusStatus == StatusStatusEnum::Busy);
    }

    SECTION("Test Search by Pin")
    {
        auto found = SensorSet.find({.Pin=300});
        REQUIRE(found == SensorSet.end());
    }
}
