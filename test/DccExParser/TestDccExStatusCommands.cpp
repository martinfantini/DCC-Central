#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommandConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC Status commands")
{
    using namespace DccExParser;

    // test information
    static std::unordered_map<int, bool> _getStatusSensors_map = {{125, false},{100, true} };
    static std::string                   _info_string = "Test";

    class TestInfoInterface : public TestMockInfoInterface
    {
        public:
            const std::string& getAdditionVersionInfo()
            {
                return _info_string;
            }
    };

    class TestTurnoutInterface : public TestMockTurnoutInterface
    {

    };

    class TestSensorsInterface : public TestMockSensorsInterface
    {
        virtual const std::unordered_map<int, bool> getStatusSensors()
        {
            return _getStatusSensors_map;
        }
    };

    class TestTrackInterface : public TestMockTrackInterface
    {
        virtual bool isTrackOn(TackType eTrack)
        {
            if ((int)eTrack == 0)
                return true;
            return false;
        }
    };

    // Create the basic variables to testing.
    TestMockLocoInterface  _TestMockLocoInterface;
    TestTrackInterface _TestMockTrackInterface;
    TestSensorsInterface _TestMockSensorsInterface;
    TestTurnoutInterface _TestMockTurnoutInterface;
    TestInfoInterface _TestMockInfoInterface;
    TestMockAccessoryInterface _TestMockAccessoryInterface;
    TestMockDccTrackInterface _TestMockDccTrackInterface;

    TestMockCommandManager _TestMockCommandManager(_TestMockLocoInterface, _TestMockTrackInterface, _TestMockSensorsInterface, _TestMockTurnoutInterface, _TestMockInfoInterface, _TestMockAccessoryInterface, _TestMockDccTrackInterface);

    DccExCommandParser dccParser(_TestMockCommandManager);
    std::string commandResult;
    dccParser.set_response_callback(std::make_shared<DccExResponse>(DccExResponse(commandResult, true)));
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test Status")
    {
        dccBasicParser.read_stream("<s>\n");
        CHECK(commandResult.find("<iDCC-EX") != std::string::npos);
        CHECK(commandResult.find("<p1 MAIN>\n") != std::string::npos);
        CHECK(commandResult.find("<q 125>\n") != std::string::npos);
        CHECK(commandResult.find("<Q 100>\n") != std::string::npos);
    }
}
