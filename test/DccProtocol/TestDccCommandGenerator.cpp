#include <catch2/catch_test_macros.hpp>

#include <vector>

#include "TestDccHelpers.hpp"
#include "DccCommandGenerator.hpp"

using namespace DccProtocol;

TEST_CASE("Test Basic Bit Manipulation")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);

    SECTION("Test high and low part case")
    {
        CHECK(_DccCommandGenerator.HighByte(0xFFEA) == static_cast<char>(0xFF));
        CHECK(_DccCommandGenerator.HighByte(0x00EA) == static_cast<char>(0x00));
        CHECK(_DccCommandGenerator.HighByte(0xCEFA) == static_cast<char>(0xCE));

        CHECK(_DccCommandGenerator.LowByte(0xFFEA) == static_cast<char>(0xEA));
        CHECK(_DccCommandGenerator.LowByte(0x00EA) == static_cast<char>(0xEA));
    }
}

TEST_CASE("Test Checksum Calculation")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);

    SECTION("Test empty vector")
    {
        std::vector<char> values_vector;
        CHECK(!_DccCommandGenerator.CalculateCheckSum(values_vector));
    }

    SECTION("Test normal case")
    {
        std::vector<char> values_vector;
        values_vector.push_back(static_cast<char>(0xFF));
        values_vector.push_back(static_cast<char>(0xFF));
        CHECK(_DccCommandGenerator.CalculateCheckSum(values_vector));
        CHECK(values_vector.size() == 3);
        CHECK(values_vector[0] == static_cast<char>(0xFF));
        CHECK(values_vector[1] == static_cast<char>(0xFF));
        CHECK(values_vector[2] == static_cast<char>(0x00));
    }

    SECTION("Test too bing vector")
    {
        std::vector<char> values_vector;
        values_vector.push_back(static_cast<char>(0xFF));
        values_vector.push_back(static_cast<char>(0xFF));
        values_vector.push_back(static_cast<char>(0x00));
        values_vector.push_back(static_cast<char>(0x01));
        values_vector.push_back(static_cast<char>(0x55));
        values_vector.push_back(static_cast<char>(0x66));
        CHECK(!_DccCommandGenerator.CalculateCheckSum(values_vector));
    }

    SECTION("Test another use case")
    {
        std::vector<char> values_vector;
        values_vector.push_back(static_cast<char>(0xAF));
        values_vector.push_back(static_cast<char>(0x55));
        values_vector.push_back(static_cast<char>(0x03));
        CHECK(_DccCommandGenerator.CalculateCheckSum(values_vector));
        CHECK(values_vector.size() == 4);
        CHECK(values_vector[0] == static_cast<char>(0xAF));
        CHECK(values_vector[1] == static_cast<char>(0x55));
        CHECK(values_vector[2] == static_cast<char>(0x03));
        CHECK(values_vector[3] == static_cast<char>(0xF9));
    }
}

TEST_CASE("Test Address calculation")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);

    SECTION("Test basic address")
    {
        std::vector<char> values_vector;
        _DccCommandGenerator.AddressEncoding(15, values_vector);
        CHECK(values_vector.size() == 1);
        CHECK(values_vector[0] == 15);
        CHECK(static_cast<char>(values_vector[0]) == static_cast<char>(0x0F));
    }

    SECTION("Test high address")
    {
        std::vector<char> values_vector;
        _DccCommandGenerator.AddressEncoding(129, values_vector);
        CHECK(values_vector.size() == 2);
        CHECK(values_vector[0] == 15);
        CHECK(values_vector[1] == 15);
    }

    SECTION("Test small address")
    {
        std::vector<char> values_vector;
    }
}

/*
    void DccCommandGenerator::AddressEncoding(int cab, std::vector<char>& values)
    {
        if (cab > HIGHEST_SHORT_ADDR)
            values.push_back(highByte(cab) | 0xC0);
        values.push_back(cab);          
    }
*/