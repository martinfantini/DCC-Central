#include <catch2/catch_test_macros.hpp>

#include "TurnoutCache.hpp"

TEST_CASE("Test Turnout Map")
{
    using namespace Common;

    TurnoutCache TurnoutCache;

    {
        Turnout value = { .Id = 123, .Address = 123, .Pin = 1, .Status = StatusTurnout::Close};
        TurnoutCache.Insert(std::move(value));
    }

    {
        Turnout value = { .Id = 23, .Address = 23, .Pin = 2, .Status = StatusTurnout::Throw};
        TurnoutCache.Insert(std::move(value));
    }

    SECTION("Test Search by Address")
    {
        auto found = TurnoutCache.GetTurnoutByAddressSubAddress(123);
        REQUIRE(found != nullptr);
        REQUIRE(found->Pin == 1);
    }

    SECTION("Test Search by Pin")
    {
        auto found = TurnoutCache.GetTurnoutByPin(2);
        REQUIRE(found != nullptr);
        REQUIRE(found->Address == 23);
    }    
}
