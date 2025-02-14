#include <catch2/catch_test_macros.hpp>

#include "LocoCache.hpp"

TEST_CASE("Test Loco Map")
{
    using namespace Common;

    LocoCache m_locoCache;

    {
        Loco value = { .Id = 1, .Address = 123,  .Speed = 10, .Direction = false, .FunctionIndicator = LocoFunctionsGroup::F5_F12,  .FunctionStatus = {} };
        m_locoCache.Insert(std::move(value));
    }
    
    {
        Loco value = { .Id = 3, .Address = 128, .Speed = 10, .Direction = true, .FunctionIndicator = LocoFunctionsGroup::F13_F20,  .FunctionStatus = {} };
        m_locoCache.Insert(std::move(value));
    }

    {
        Loco value = { .Id = 2, .Address = 256, .Speed = 10, .Direction = false, .FunctionIndicator = LocoFunctionsGroup::F21_F28,  .FunctionStatus = {} };
        m_locoCache.Insert(std::move(value));
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
        REQUIRE(found->Speed == 10);
    }
}