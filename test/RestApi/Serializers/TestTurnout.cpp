#include <catch2/catch_test_macros.hpp>
#include <Serializers/Turnout.hpp>

using namespace RestApi::Serializer;
using namespace Common;

TEST_CASE("Turnout to json","[Turnout_ToJson]")
{
    int Id = 10;
    int Address = 115;
    int SubAddress = 4;
    int Pin = 10;
    StatusTurnout Status = StatusTurnout::Close;

    Turnout turnout = {.Id = Id, .Address = Address, .SubAddress = SubAddress, .Pin = Pin, .Status = Status};

    auto resultObject = ToJson(turnout);

    CHECK(resultObject.at("Id").as_int64() == Id);
    CHECK(resultObject.at("Address").as_int64() == Address);
    CHECK(resultObject.at("SubAddress").as_int64() == SubAddress);
    CHECK(resultObject.at("Pin").as_int64() == Pin);
    CHECK(resultObject.at("Status").as_string() == "Close");
}

TEST_CASE("Turnout From json","[Turnout_FromJson]")
{
    int Id = 10;
    int Address = 115;
    int SubAddress = 4;
    int Pin = 10;
    StatusTurnout Status = StatusTurnout::Throw;

    boost::json::object turnoutObj;
    turnoutObj["Id"] = Id;
    turnoutObj["Address"] = Address;
    turnoutObj["SubAddress"] = SubAddress;
    turnoutObj["Pin"] = Pin;
    turnoutObj["Status"] = "Throw";

    Turnout turnout = FromJson(turnoutObj);

    CHECK(turnout.Id == Id);
    CHECK(turnout.Address == Address);
    CHECK(turnout.SubAddress == SubAddress);
    CHECK(turnout.Pin == Pin);
    CHECK(turnout.Status == Status);
}
