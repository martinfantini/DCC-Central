#include <catch2/catch_test_macros.hpp>
#include <Serializers/Sensor.hpp>

using namespace RestApi::Serializer;

TEST_CASE("Sensor to json","[Sensor_ToJson]")
{
    int Id = 10;
    int Pin = 10;
    bool PullUp = true;
    SensorStatusEnum Status = SensorStatusEnum::Busy;

    Sensor sensor = {.Id = Id, .Pin = Pin, .PullUp = PullUp, .Status = Status};

    auto resultObject = ToJson(sensor);

    CHECK(resultObject.at("Id").as_int64() == Id);
    CHECK(resultObject.at("Pin").as_int64() == Pin);
    CHECK(resultObject.at("PullUp").as_bool() == PullUp);
    CHECK(resultObject.at("Status").as_int64() == (int) Status);
}

TEST_CASE("Sensor From json","[Sensor_FromJson]")
{
    int Id = 10;
    int Pin = 10;
    bool PullUp = true;
    SensorStatusEnum Status = SensorStatusEnum::Busy;

    boost::json::object obj;
    obj["Id"] = Id;
    obj["Pin"] = Pin;
    obj["PullUp"] = PullUp;
    obj["Status"] = "Close";

    Sensor sensorResult = FromJson(obj);

    CHECK(sensorResult.Id == Id);
    CHECK(sensorResult.Pin == Pin);
    CHECK(sensorResult.PullUp == PullUp);
    CHECK(sensorResult.Status == (int) Status);
}
