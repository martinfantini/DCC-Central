#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommandConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC implemented commands")
{
    using namespace DccExParser;

    // Create the basic variables to testing.
    TestMockLocoInterface  _TestMockLocoInterface;
    TestMockTrackInterface _TestMockTrackInterface;
    TestMockSensorsInterface _TestMockSensorsInterface;
    TestMockTurnoutInterface _TestMockTurnoutInterface;
    TestMockInfoInterface _TestMockInfoInterface;
    TestMockAccessoryInterface _TestMockAccessoryInterface;
    TestMockDccTrackInterface _TestMockDccTrackInterface;

    TestMockCommandManager _TestMockCommandManager(_TestMockLocoInterface, _TestMockTrackInterface, _TestMockSensorsInterface, _TestMockTurnoutInterface, _TestMockInfoInterface, _TestMockAccessoryInterface, _TestMockDccTrackInterface);

    DccExCommandParser dccParser(_TestMockCommandManager);
    std::string commandResult;
    dccParser.set_response_callback(std::make_shared<DccExResponse>(DccExResponse(commandResult)));
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test empty case")
    {
        dccBasicParser.read_stream("< >\n");
        CHECK(commandResult == "<X>\n");
    }
}