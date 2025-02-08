#include <catch2/catch_test_macros.hpp>

#include "AccessoryDecoder.hpp"

TEST_CASE("Test Accessory Decoder Map")
{
    using namespace Common::AddresDecoderInformation;

    SECTION("Test one insertion")
    {
        AccessoryMap.clear();
        {
            Accessory value = { .Address=123, .SubAddress=0, .isActive=true, .isOn=true };
            AccessoryMap.emplace(std::move(value));
        }

        REQUIRE(AccessoryMap.size() == 1);
        auto found = AccessoryMap.find({ .Address=123, .SubAddress=0 });
        REQUIRE( found != AccessoryMap.end() );
        REQUIRE( found->isActive );
        REQUIRE( found->isOn );
    }

    SECTION("Test more insertions")
    {
        AccessoryMap.clear();
        {
            Accessory value = { .Address=123, .SubAddress=0, .isActive=true, .isOn=true };
            AccessoryMap.emplace(std::move(value));
        }      

        {
            Accessory value = { .Address=124, .SubAddress=4, .isActive=true, .isOn=true };
            AccessoryMap.emplace(std::move(value));
        }

        {
            auto found = AccessoryMap.find({ .Address=124, .SubAddress=4 });
            REQUIRE( found != AccessoryMap.end() );
            REQUIRE( found->isActive );
            REQUIRE( found->isOn );
        }

        {
            auto found = AccessoryMap.find({ .Address=128, .SubAddress=4 });
            REQUIRE( found == AccessoryMap.end() );
        }
    }
}
