#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommandConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC Info implemented commands")
{
    using namespace DccExParser;

    static std::string info_string;

    std::string commandResult;
    DccExParser::string_function_type commandFunction = [&commandResult](const std::string& command_result)
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
    TestMockAccessoryInterface _TestMockAccessoryInterface;
    TestMockDccTrackInterface _TestMockDccTrackInterface;

    TestMockCommandManager _TestMockCommandManager(_TestMockLocoInterface, _TestMockTrackInterface, _TestMockSensorsInterface, _TestMockTurnoutInterface, _TestMockInfoInterface, _TestMockAccessoryInterface, _TestMockDccTrackInterface);

    DccExCommandParser dccParser(_TestMockCommandManager, commandFunction);
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test empty case")
    {
        dccBasicParser.read_stream("< >\n");
        CHECK(commandResult == "<X>\n");
    }
}