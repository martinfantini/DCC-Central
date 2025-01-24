#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommadConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC Info implemented commands")
{
    using namespace DccExParser;

    static std::string info_string;
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

   class TestInfoInterface : public InfoInterface
    {
        public:
            const std::string& getAdditionVersionInfo()
            {
                return info_string;
            }
    };
    // Create the basic variables to testing.
    TestMockLocoInterface  _TestMockLocoInterface;
    TestMockTrackInterface _TestMockTrackInterface;
    TestMockSensorsInterface _TestMockSensorsInterface;
    TestMockTurnoutInterface _TestMockTurnoutInterface;
    TestInfoInterface _TestMockInfoInterface;

    TestMockCommandManager _TestMockCommandManager(_TestMockLocoInterface, _TestMockTrackInterface, _TestMockSensorsInterface, _TestMockTurnoutInterface, _TestMockInfoInterface);

    DccExCommandParser dccParser(_TestMockCommandManager, commandFunction, loggerFunction);
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test empty case")
    {
        dccBasicParser.read_stream("< >\n");
        CHECK(commandResult == "<X>\n");
    }
}