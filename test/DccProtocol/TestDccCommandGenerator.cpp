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
        CHECK(_DccCommandGenerator.HighByte(0xFFEA) == static_cast<unsigned char>(0xFF));
        CHECK(_DccCommandGenerator.HighByte(0x00EA) == static_cast<unsigned char>(0x00));
        CHECK(_DccCommandGenerator.HighByte(0xCEFA) == static_cast<unsigned char>(0xCE));

        CHECK(_DccCommandGenerator.LowByte(0xFFEA) == static_cast<unsigned char>(0xEA));
        CHECK(_DccCommandGenerator.LowByte(0x00EA) == static_cast<unsigned char>(0xEA));
    }
}

TEST_CASE("Test Checksum Calculation")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);

    SECTION("Test empty vector")
    {
        std::vector<unsigned char> values_vector;
        CHECK(!_DccCommandGenerator.CalculateCheckSum(values_vector));
    }

    SECTION("Test normal case")
    {
        std::vector<unsigned char> values_vector;
        values_vector.push_back(static_cast<unsigned char>(0xFF));
        values_vector.push_back(static_cast<unsigned char>(0xFF));
        CHECK(_DccCommandGenerator.CalculateCheckSum(values_vector));
        CHECK(values_vector.size() == 3);
        CHECK(values_vector[0] == static_cast<unsigned char>(0xFF));
        CHECK(values_vector[1] == static_cast<unsigned char>(0xFF));
        CHECK(values_vector[2] == static_cast<unsigned char>(0x00));
    }

    SECTION("Test too bing vector")
    {
        std::vector<unsigned char> values_vector;
        values_vector.push_back(static_cast<unsigned char>(0xFF));
        values_vector.push_back(static_cast<unsigned char>(0xFF));
        values_vector.push_back(static_cast<unsigned char>(0x00));
        values_vector.push_back(static_cast<unsigned char>(0x01));
        values_vector.push_back(static_cast<unsigned char>(0x55));
        values_vector.push_back(static_cast<unsigned char>(0x66));
        CHECK(!_DccCommandGenerator.CalculateCheckSum(values_vector));
    }

    SECTION("Test another use case")
    {
        std::vector<unsigned char> values_vector;
        values_vector.push_back(static_cast<unsigned char>(0xAF));
        values_vector.push_back(static_cast<unsigned char>(0x55));
        values_vector.push_back(static_cast<unsigned char>(0x03));
        CHECK(_DccCommandGenerator.CalculateCheckSum(values_vector));
        CHECK(values_vector.size() == 4);
        CHECK(values_vector[0] == static_cast<unsigned char>(0xAF));
        CHECK(values_vector[1] == static_cast<unsigned char>(0x55));
        CHECK(values_vector[2] == static_cast<unsigned char>(0x03));
        CHECK(values_vector[3] == static_cast<unsigned char>(0xF9));
    }
}

TEST_CASE("Test Address calculation")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);

    SECTION("Test basic address")
    {
        std::vector<unsigned char> values_vector;
        _DccCommandGenerator.AddressEncoding(15, values_vector);
        CHECK(values_vector.size() == 1);
        CHECK(values_vector[0] == 15);
        CHECK(static_cast<unsigned char>(values_vector[0]) == static_cast<unsigned char>(0x0F));
    }

    SECTION("Test high address")
    {
        std::vector<unsigned char> values_vector;
        _DccCommandGenerator.AddressEncoding(129, values_vector);
        CHECK(values_vector.size() == 2);
        CHECK(values_vector[0] == static_cast<unsigned char>(0xC0));
        CHECK(values_vector[1] ==  static_cast<unsigned char>(0x81));
    }

    SECTION("Test high address")
    {
        std::vector<unsigned char> values_vector;
        _DccCommandGenerator.AddressEncoding(600, values_vector);
        CHECK(values_vector.size() == 2);
        CHECK(values_vector[0] == static_cast<unsigned char>(0xC2));
        CHECK(values_vector[1] == static_cast<unsigned char>(0x58));
    }
}

TEST_CASE("Test Function F1 to F4")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);
    
    SECTION("Test Bad function")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;
        _DccCommandGenerator.SetFunction_F1_F4(0, true, instruction, function);
        CHECK(instruction.size() == 0);

        _DccCommandGenerator.SetFunction_F1_F4(5, true, instruction, function);
        CHECK(instruction.size() == 0);
    }

    SECTION("Test One Call")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;
        _DccCommandGenerator.SetFunction_F1_F4(1, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0x11));
    }

    SECTION("Test Two Call")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;
        _DccCommandGenerator.SetFunction_F1_F4(1, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0x11));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F1_F4(4, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x09));
        CHECK(instruction[0] == static_cast<unsigned char>(0x19));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F1_F4(3, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x0D));
        CHECK(instruction[0] == static_cast<unsigned char>(0x1D));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F1_F4(3, false, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x09));
        CHECK(instruction[0] == static_cast<unsigned char>(0x19));
    }
}

TEST_CASE("Test Function F5 to F12")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);
    
    SECTION("Test Bad function")
    {
        unsigned char function;
        std::vector<unsigned char> instruction;
        _DccCommandGenerator.SetFunction_F5_F12(4, true, instruction, function);
        CHECK(instruction.size() == 0);

        _DccCommandGenerator.SetFunction_F5_F12(13, true, instruction, function);
        CHECK(instruction.size() == 0);
    }

    SECTION("Test Two Call Low")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;
        _DccCommandGenerator.SetFunction_F5_F12(5, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xA1));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F5_F12(6, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x03));
        CHECK(instruction[0] == static_cast<unsigned char>(0xA3));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F5_F12(8, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x0B));
        CHECK(instruction[0] == static_cast<unsigned char>(0xAB));
    }

    SECTION("Test Two Call High")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;

        _DccCommandGenerator.SetFunction_F5_F12(12, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x80));
        CHECK(instruction[0] == static_cast<unsigned char>(0xB8));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F5_F12(11, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0xC0));
        CHECK(instruction[0] == static_cast<unsigned char>(0xBC));        
    }

    SECTION("Test Mixed")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;

        _DccCommandGenerator.SetFunction_F5_F12(5, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xA1));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F5_F12(12, true, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x81));
        CHECK(instruction[0] == static_cast<unsigned char>(0xB8));
    
        instruction.clear();
        _DccCommandGenerator.SetFunction_F5_F12(12, false, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xB0));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F5_F12(5, false, instruction, function);
        CHECK(instruction.size() == 1);
        CHECK(function == static_cast<unsigned char>(0x00));
        CHECK(instruction[0] == static_cast<unsigned char>(0xA0));        
    }
}

TEST_CASE("Test Function F13 to F20")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);
    
    SECTION("Test Mixed")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;

        _DccCommandGenerator.SetFunction_F13_F20(13, true, instruction, function);
        CHECK(instruction.size() == 2);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xDE));
        CHECK(instruction[1] == static_cast<unsigned char>(0x01));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F13_F20(17, true, instruction, function);
        CHECK(instruction.size() == 2);
        CHECK(function == static_cast<unsigned char>(0x11));
        CHECK(instruction[0] == static_cast<unsigned char>(0xDE));
        CHECK(instruction[1] == static_cast<unsigned char>(0x11));
    
        instruction.clear();
        _DccCommandGenerator.SetFunction_F13_F20(17, false, instruction, function);
        CHECK(instruction.size() == 2);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xDE));
        CHECK(instruction[1] == static_cast<unsigned char>(0x01));
    }
}

TEST_CASE("Test Function F21 to F28")
{
    TestMockDccInterface _TestMockDccInterface;
    DccCommandGenerator _DccCommandGenerator(_TestMockDccInterface);

    SECTION("Test Mixed")
    {
        unsigned char function = 0x00;
        std::vector<unsigned char> instruction;

        _DccCommandGenerator.SetFunction_F21_F28(21, true, instruction, function);
        CHECK(instruction.size() == 2);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xD8));
        CHECK(instruction[1] == static_cast<unsigned char>(0x01));

        instruction.clear();
        _DccCommandGenerator.SetFunction_F21_F28(25, true, instruction, function);
        CHECK(instruction.size() == 2);
        CHECK(function == static_cast<unsigned char>(0x11));
        CHECK(instruction[0] == static_cast<unsigned char>(0xD8));
        CHECK(instruction[1] == static_cast<unsigned char>(0x11));
    
        instruction.clear();
        _DccCommandGenerator.SetFunction_F21_F28(25, false, instruction, function);
        CHECK(instruction.size() == 2);
        CHECK(function == static_cast<unsigned char>(0x01));
        CHECK(instruction[0] == static_cast<unsigned char>(0xD8));
        CHECK(instruction[1] == static_cast<unsigned char>(0x01));
    }
}
