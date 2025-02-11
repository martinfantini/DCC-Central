#include <catch2/catch_test_macros.hpp>

#include "Configuration.hpp"

TEST_CASE("Test global Configuration class")
{
    using namespace Central::Configuration;
    SECTION("Test default configuration")
    {
        Config _config;
        REQUIRE( not _config.isRestApiEnabled());
        REQUIRE( not _config.isLoggerEnabled());
        REQUIRE( not _config.isDCCEnabled());
    }
}