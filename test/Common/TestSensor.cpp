#include <catch2/catch_test_macros.hpp>

#include "SensorCache.hpp"

TEST_CASE("Test Sensor Set")
{
    using namespace Common;
    SensorCache SensorCache;

    {
        Sensor value = { .Id=123, .Pin=123, .Status=SensorStatusEnum::Busy};
        SensorCache.Insert(std::move(value));
    }

    {
        Sensor value = { .Id=128, .Pin=128, .Status=SensorStatusEnum::Free};
        SensorCache.Insert(std::move(value));
    }

    {
        Sensor value = { .Id=125, .Pin=125, .Status=SensorStatusEnum::Free};
        SensorCache.Insert(std::move(value));
    }

    SECTION("Test Search by Pin")
    {
        auto found = SensorCache.GetSensorByPin(123);
        REQUIRE(found != nullptr);
        REQUIRE(found->Status == SensorStatusEnum::Busy);
    }

    SECTION("Test Search by Id")
    {
        auto found = SensorCache.GetSensorById(128);
        REQUIRE(found != nullptr);
        REQUIRE(found->Status == SensorStatusEnum::Free);
    }

    SECTION("Test Search Not found")
    {
        auto found = SensorCache.GetSensorById(500);
        REQUIRE(found == nullptr);
    }
}
