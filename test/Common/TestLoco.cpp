#include <catch2/catch_test_macros.hpp>

#include "LocoCache.hpp"

TEST_CASE("Test Loco Map")
{
    using namespace Common::LocoInformation;

    LocoCache m_locoCache;

    {
        Loco value = { .Address = 123, .Id = 1, .currentSpeed = 10, .currentDirection = false, .functionIndicator = LocoFunctionsGroup::F5_F12,  .functionStatus = {} };
        m_locoCache.insert(std::move(value));
    }
    
    {
        Loco value = { .Address = 128, .Id = 3, .currentSpeed = 10, .currentDirection = true, .functionIndicator = LocoFunctionsGroup::F13_F20,  .functionStatus = {} };
        m_locoCache.insert(std::move(value));
    }

    {
        Loco value = { .Address = 256, .Id = 2, .currentSpeed = 10, .currentDirection = false, .functionIndicator = LocoFunctionsGroup::F21_F28,  .functionStatus = {} };
        m_locoCache.insert(std::move(value));
    }

    SECTION("Test Search by Address")
    {
        auto found = m_locoCache.GetLocoByAddress(123);
        REQUIRE(found != nullptr);
        REQUIRE(found->Id == 1);
    }

    SECTION("Test Search by Id")
    {
        auto found = m_locoCache.GetLocoById(2);
        REQUIRE(found != nullptr);
        REQUIRE(found->Address == 256);
    }

    SECTION("Test Search by Addres and Id")
    {
        auto found = m_locoCache.GetLocoByIdAddress(3, 128);
        REQUIRE(found != nullptr);
        REQUIRE(found->currentSpeed == 10);
    }
}