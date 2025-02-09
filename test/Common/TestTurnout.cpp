#include <catch2/catch_test_macros.hpp>

#include "TurnoutCache.hpp"

TEST_CASE("Test Turnout Map")
{
    using namespace Common::TurnoutInformation;

    TurnoutCache m_TurnoutCache;

    {
        Turnout value = { .Address = 123, .Pin = 1, .Status = StatusTurnout::Close};
        m_TurnoutCache.insert(std::move(value));
    }
    
    {
        Turnout value = { .Address = 23, .Pin = 2, .Status = StatusTurnout::Throw};
        m_TurnoutCache.insert(std::move(value));
    }

    SECTION("Test Search by Address")
    {
        auto found = m_TurnoutCache.GetTurnoutByAddress(123);
        REQUIRE(found != nullptr);
        REQUIRE(found->Pin == 1);
    }

    SECTION("Test Search by Pin")
    {
        auto found = m_TurnoutCache.GetTurnoutByPin(2);
        REQUIRE(found != nullptr);
        REQUIRE(found->Address == 23);
    }    
}
