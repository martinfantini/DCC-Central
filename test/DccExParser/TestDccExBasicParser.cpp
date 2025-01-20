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
            void parsed_values(const char command, const std::vector<std::string>& parameters)
            {
                _command = command;
                _result_values = parameters;
            }

            char _command;
            std::vector<std::string> _result_values;
    };

    class TestAppendCallbackParser : public CallbackParser
    {
        public:
            void parsed_values(const char command, const std::vector<std::string>& parameters)
            {
                if (_is_first_command)
                {
                    _first_command = command;
                    _first_result_values = parameters;
                    _is_first_command = false;
                }
                else
                {
                    _second_command = command;
                    _second_result_values = parameters;

                }
            }
        
            bool _is_first_command = true;

            char _first_command;
            std::vector<std::string> _first_result_values;

            char _second_command;
            std::vector<std::string> _second_result_values;
    };

    SECTION("Basic test parser")
    {
        TestCallbackParser testCallbackParser;
        DCCBasicParser parser(testCallbackParser);

        parser.read_stream("<m 20 34 10>");
        REQUIRE( testCallbackParser._command == 'm');
        REQUIRE( testCallbackParser._result_values.size() == 3);
        REQUIRE( testCallbackParser._result_values[0] == "20");
        REQUIRE( testCallbackParser._result_values[1] == "34");
        REQUIRE( testCallbackParser._result_values[2] == "10");
    }

    SECTION("Middle command")
    {
        TestCallbackParser testCallbackParser;
        DCCBasicParser parser(testCallbackParser);

        parser.read_stream("10 23 43<m 20 34 10> 58 69");
        REQUIRE( testCallbackParser._command == 'm');
        REQUIRE( testCallbackParser._result_values.size() == 3);
        REQUIRE( testCallbackParser._result_values[0] == "20");
        REQUIRE( testCallbackParser._result_values[1] == "34");
        REQUIRE( testCallbackParser._result_values[2] == "10");
    }

    SECTION("Two commands")
    {
        TestAppendCallbackParser testCallbackParser;
        DCCBasicParser parser(testCallbackParser);
         
        parser.read_stream("10 23 43<m 20 34 10> 58 69 <j 10 15 5>526 59");

        REQUIRE( testCallbackParser._first_command == 'm');
        REQUIRE( testCallbackParser._first_result_values.size() == 3);
        REQUIRE( testCallbackParser._first_result_values[0] == "20");
        REQUIRE( testCallbackParser._first_result_values[1] == "34");
        REQUIRE( testCallbackParser._first_result_values[2] == "10");

        REQUIRE( testCallbackParser._second_command == 'j');
        REQUIRE( testCallbackParser._second_result_values.size() == 3);
        REQUIRE( testCallbackParser._second_result_values[0] == "10");
        REQUIRE( testCallbackParser._second_result_values[1] == "15");
        REQUIRE( testCallbackParser._second_result_values[2] == "5");
    }
}
