#include <catch2/catch_test_macros.hpp>
#include <Serializers/Loco.hpp>
#include <algorithm>

using namespace RestApi::Serializer;
using namespace Common;

TEST_CASE("Loco to json","[Loco_ToJson]")
{
    int Id = 8;
    int Address = 10;
    int Speed = 5;
    SpeedStepsLabel SpeedSteps = SpeedStepsLabel::Steps_128;
    bool Direction = true;
    LocoFunctionsGroup FunctionIndicator = LocoFunctionsGroup::F5_F12;
    std::vector<unsigned char> FunctionStatus = { 0x0A, 0x0B, 0x00, 0x00 };

    Loco loco = {
        .Id = Id,
        .Address = Address,
        .SpeedSteps = SpeedSteps,
        .Direction=Direction,
        .FunctionIndicator=FunctionIndicator,
        .FunctionStatus=FunctionStatus };

    auto result = LocoSerializer::ToJson(loco);

    CHECK(result.at("Id").as_int64() == Id);
    CHECK(result.at("Address").as_int64() == Address);
    CHECK(result.at("SpeedSteps").as_string() == "128");
    CHECK(result.at("Direction").as_bool() == Direction);
    CHECK(result.at("FunctionIndicator").as_string() == "F5_F12");
}

TEST_CASE("Loco From json","[Loco_FromJson]")
{
    int Id = 8;
    int Address = 10;
    int Speed = 5;
    SpeedStepsLabel SpeedSteps = SpeedStepsLabel::Steps_28;
    bool Direction = true;
    LocoFunctionsGroup FunctionIndicator = LocoFunctionsGroup::F13_F20;
    std::vector<unsigned char> FunctionStatus = { 0x00, 0x00, 0x00, 0x00 };

    boost::json::object obj;
    obj["Id"] = Id;
    obj["Address"] = Address;
    obj["Speed"] = Speed;
    obj["SpeedSteps"] = "28";
    obj["Direction"] = Direction;
    obj["FunctionIndicator"] = "F13_F20";

    Loco result = LocoSerializer::FromJson(obj);

    CHECK(result.Id == Id);
    CHECK(result.Address == Address);
    CHECK(result.Speed == Speed);
    CHECK(result.SpeedSteps == SpeedSteps);
    CHECK(result.Direction == Direction);
    CHECK(result.FunctionIndicator == FunctionIndicator);
    CHECK(std::equal(result.FunctionStatus.begin(), result.FunctionStatus.end(), FunctionStatus.begin(), FunctionStatus.end()));
}
