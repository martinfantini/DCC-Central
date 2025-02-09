#include <catch2/catch_test_macros.hpp>

#include "AccessoryDecoder.hpp"

TEST_CASE("Test Accessory Decoder Set")
{
    using namespace Common::AddresDecoderInformation;
    accessory_set_type AccessorySet;

    SECTION("Test one insertion")
    {
        AccessorySet.clear();
        {
            Accessory value = { .Address=123, .SubAddress=0, .isActive=true, .isOn=true };
            AccessorySet.emplace(std::move(value));
        }

        REQUIRE(AccessorySet.size() == 1);
        auto found = AccessorySet.find({ .Address=123, .SubAddress=0 });
        REQUIRE( found != AccessorySet.end() );
        REQUIRE( found->isActive );
        REQUIRE( found->isOn );
    }

    SECTION("Test more insertions")
    {
        AccessorySet.clear();
        {
            Accessory value = { .Address=123, .SubAddress=0, .isActive=true, .isOn=true };
            AccessorySet.emplace(std::move(value));
        }      

        {
            Accessory value = { .Address=124, .SubAddress=4, .isActive=true, .isOn=true };
            AccessorySet.emplace(std::move(value));
        }

        {
            auto found = AccessorySet.find({ .Address=124, .SubAddress=4 });
            REQUIRE( found != AccessorySet.end() );
            REQUIRE( found->isActive );
            REQUIRE( found->isOn );
        }

        {
            auto found = AccessorySet.find({ .Address=128, .SubAddress=4 });
            REQUIRE( found == AccessorySet.end() );
        }
    }
}
