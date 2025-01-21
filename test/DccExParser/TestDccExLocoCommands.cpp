#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommadConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC loco implemented commands")
{
    using namespace DccExParser;

    static int max_locos = 20;

    std::string logger;
    DccExParser::string_function loggerFunction = [&logger](const std::string& logger_parser)
    {
        logger = logger_parser;
    };

    std::string commandResult;
    DccExParser::string_function commandFunction = [&commandResult](const std::string& command_result)
    {
        commandResult = command_result;
    };

   class TestLocoInterface : public LocoInterface
    {
        public:
            int getMaxLocos()
            {
                return max_locos;
            }
            void setFunction(int lok_id, int function_number, bool on)
            {
                return;
            }
            int lookupLoco(int locoId)
            {
                return 0;
            }
            
            bool createLoco(int locoId)
            {
                return true;
            }
            void removeLoco(int)
            {}

            void removeAllLocos()
            {}

            void emergencyStopLoco(int)
            {}
    };

    TestMockTrackInterface _testTrackInterface;
    TestLocoInterface _testLocoInterface;

    TestMockCommandManager commandTester(_testLocoInterface, _testTrackInterface);
    DccExCommandParser dccParser(commandTester, commandFunction, loggerFunction);
    DCCBasicParser dccBasicParser(dccParser);


    SECTION("Test # case")
    {
        max_locos = 20;
        dccBasicParser.read_stream("<#>\n");
        CHECK(commandResult == "<# " + std::to_string(max_locos) +">\n");
    }

    SECTION("Test empty case")
    {
        dccBasicParser.read_stream("< >\n");
        CHECK(commandResult == "<X>");
    }
}