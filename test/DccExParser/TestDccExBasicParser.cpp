#include <catch2/catch_test_macros.hpp>

#include "DccExBasicParser.hpp"

#include<string>
#include<vector>

TEST_CASE("Test DCC command parser")
{
    using namespace DccExParser;

    class TestCallbackParser : public CallbackParser
    {
        public:
            TestCallbackParser(std::vector<std::string>& result_values):
                _result_values(result_values)
            {}

        private: 
            void parsed_values(const std::vector<std::string>& parsed_values)
            {
                _result_values = parsed_values;
            }
        
            std::vector<std::string>& _result_values;
    };

    class TestAppendCallbackParser : public CallbackParser
    {
        public:
            TestAppendCallbackParser(std::vector<std::string>& result_values):
                _result_values(result_values)
            {}

        private: 
            void parsed_values(const std::vector<std::string>& parsed_values)
            {
                _result_values.insert(_result_values.end(), parsed_values.begin(), parsed_values.end());
            }
        
            std::vector<std::string>& _result_values;
    };

    SECTION("Basic test parser")
    {
        std::vector<std::string> result_values = {};
        TestCallbackParser testCallbackParser(result_values);
        DCCBasicParser parser(testCallbackParser);
        
        parser.read_stream("<m 20 34 10>");
        REQUIRE( result_values.size() == 4);
        REQUIRE( result_values[0] == "m");
        REQUIRE( result_values[1] == "20");
        REQUIRE( result_values[2] == "34");
        REQUIRE( result_values[3] == "10");
    }

    SECTION("Middle command")
    {
        std::vector<std::string> result_values = {};
        TestCallbackParser testCallbackParser(result_values);
        DCCBasicParser parser(testCallbackParser);
        
        parser.read_stream("10 23 43<m 20 34 10> 58 69");
        REQUIRE( result_values.size() == 4);
        REQUIRE( result_values[0] == "m");
        REQUIRE( result_values[1] == "20");
        REQUIRE( result_values[2] == "34");
        REQUIRE( result_values[3] == "10");
    }

    SECTION("Two commands")
    {
        std::vector<std::string> result_values = {};
        TestAppendCallbackParser testCallbackParser(result_values);
        DCCBasicParser parser(testCallbackParser);
         
        parser.read_stream("10 23 43<m 20 34 10> 58 69 <j 10 15 5>526 59");
        REQUIRE( result_values.size() == 8);

        REQUIRE( result_values[0] == "m");
        REQUIRE( result_values[1] == "20");
        REQUIRE( result_values[2] == "34");
        REQUIRE( result_values[3] == "10");

        REQUIRE( result_values[4] == "j");
        REQUIRE( result_values[5] == "10");
        REQUIRE( result_values[6] == "15");
        REQUIRE( result_values[7] == "5");
    }     
}