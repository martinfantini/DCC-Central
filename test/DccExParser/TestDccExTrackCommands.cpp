#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommadConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC track implemented commands")
{
    using namespace DccExParser;

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

    static std::vector<bool> _status = {false, false, false};
    static std::vector<bool> _enabled = {false, false, false};

    class TestTrackInterface : public TrackInterface
    {
        public:
            bool isTrackEnabled(TrackInterface::TackType _type)
            {
                return _enabled[(int) _type];
            }
            bool isTrackOn(TrackInterface::TackType _type)
            {
                return _status[(int) _type];
            }

            void turnOnTrack(TrackInterface::TackType _type)
            {
                _status[(int) _type] = true;
            }

            void turnOffTrack(TrackInterface::TackType _type)
            {
                _status[(int) _type] = false;
            }
    };

    TestTrackInterface _testTrackInterface;
    TestMockLocoInterface _testLocoInterface;

    TestMockCommandManager commandTester(_testLocoInterface, _testTrackInterface);
    DccExCommandParser dccParser(commandTester, commandFunction, loggerFunction);
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test empty case")
    {
        dccBasicParser.read_stream("< >\n");
        CHECK(commandResult == "<X>");
    }

    SECTION("Test trun all off")
    {
        // set all on
        _status = {true, true, false};
        dccBasicParser.read_stream("<0>\n");
        CHECK(!_status[0]);
        CHECK(!_status[1]);
        CHECK(!_status[2]);
        CHECK(commandResult == "<p0>");
    }

    SECTION("Test trun all on")
    {
        // set all on
        _status = {false, false, false};
        dccBasicParser.read_stream("<1>\n");
        CHECK(_status[0]);
        CHECK(_status[1]);
        CHECK(!_status[2]);
        CHECK(commandResult == "<p1>");
    }

    SECTION("Test trun on Main")
    {
        // set all on
        _status = {false, false, false};
        dccBasicParser.read_stream("<1 MAIN>\n");
        CHECK(_status[0]);
        CHECK(!_status[1]);
        CHECK(!_status[2]);
        CHECK(commandResult == "<p1 MAIN>");
    }

    SECTION("Test trun off Main")
    {
        // set all on
        _status = {true, false, false};
        dccBasicParser.read_stream("<0 MAIN>\n");
        CHECK(!_status[0]);
        CHECK(!_status[1]);
        CHECK(!_status[2]);
        CHECK(commandResult == "<p0>");
    }

    SECTION("emergency Stop")
    {
        // set all on
        _status = {true, true, true};
        dccBasicParser.read_stream("<!>\n");
        CHECK(!_status[0]);
        CHECK(!_status[1]);
        CHECK(!_status[2]);
        CHECK(commandResult == "<X>");
    }    
}