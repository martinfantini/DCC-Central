#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommandConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC loco implemented commands")
{
    using namespace DccExParser;

    // Helper variables
    static int max_locos = 20;
    static bool _removeAllLocos = false;
    static int _emergencyStopLocoId = 0;
    static int _fuction_lok_id = 0;
    static int _fuction_function_number = 0;
    static bool _fuction_on = false;
    static int _lookupLoco_locoId = 0;
    static int _createLoco_locoId = 0;
    static int _removeLoco_locoId = 0;

    class TestLocoInterface : public TestMockLocoInterface
    {
        public:
            int getMaxLocos()
            {
                return max_locos;
            }

            bool setFunction(int lok_id, int function_number, bool on)
            {
                _fuction_lok_id = lok_id;
                _fuction_function_number = function_number;
                _fuction_on = on;
                return true;
            }

            virtual void updateFunction(int lok_id, int function_number)
            {
                _fuction_lok_id = lok_id;
                _fuction_function_number = function_number;
            }

            int searchLoco(int locoId)
            {
                _lookupLoco_locoId = locoId;
                return locoId;
            }
            
            bool createLoco(int locoId)
            {
                _createLoco_locoId = locoId;
                return true;
            }
            void removeLoco(int locoId)
            {
                _removeLoco_locoId = locoId;
            }

            void removeAllLocos()
            {
                _removeAllLocos = true;
            }

            void emergencyStopLoco(int _id)
            {
                _emergencyStopLocoId = _id;
            }

            void emergencyStop()
            {}

            bool setLoco(int cab, int tspeed, bool forwardDirection)
            {
                return true;
            }

            bool getLoco(int cab, int& locoId ,int& tspeed, int& functions)
            {
                return true;
            }
    };

    // Create the basic variables to testing.
    TestLocoInterface _testLocoInterface;
    TestMockTrackInterface _TestMockTrackInterface;
    TestMockSensorsInterface _TestMockSensorsInterface;
    TestMockTurnoutInterface _TestMockTurnoutInterface;
    TestMockInfoInterface _TestMockInfoInterface;
    TestMockAccessoryInterface _TestMockAccessoryInterface;
    TestMockDccTrackInterface _TestMockDccTrackInterface;

    TestMockCommandManager _TestMockCommandManager(_testLocoInterface, _TestMockTrackInterface, _TestMockSensorsInterface, _TestMockTurnoutInterface, _TestMockInfoInterface, _TestMockAccessoryInterface, _TestMockDccTrackInterface);

    DccExCommandParser dccParser(_TestMockCommandManager);
    std::string commandResult;
    dccParser.set_response_callback(std::make_shared<DccExResponse>(DccExResponse(commandResult)));
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test # case")
    {
        max_locos = 20;
        dccBasicParser.read_stream("<#>\n");
        CHECK(commandResult == "<# " + std::to_string(max_locos) +">\n");
    }

    SECTION("Test empty case")
    {
        dccBasicParser.read_stream("<->\n");
        CHECK(commandResult == "<X>\n");
    }

    SECTION("Forget all locos")
    {
        _removeAllLocos = false;
        CHECK(!_removeAllLocos);
        dccBasicParser.read_stream("<- 0>\n");
        CHECK(_removeAllLocos);
        CHECK(commandResult == "<O>\n");
    }

    SECTION("Forget loco")
    {
        _removeLoco_locoId = 0;
        CHECK(_removeLoco_locoId ==  0);
        int loco_id = 10;
        dccBasicParser.read_stream("<- " + std::to_string(loco_id) + ">\n");
        CHECK(_removeLoco_locoId == loco_id);
        CHECK(commandResult == "<O>\n");
    }

    SECTION("Function loco on")
    {
        _fuction_lok_id = 0;
        _fuction_function_number = 0;
        _fuction_on = false;        
        dccBasicParser.read_stream("<F 10 5 1>\n");
        CHECK(_fuction_lok_id == 10);
        CHECK(_fuction_function_number == 5);
        CHECK(_fuction_on);
        CHECK(commandResult == "<X>\n");
    }

    SECTION("Function loco off")
    {
        _fuction_lok_id = 0;
        _fuction_function_number = 0;
        _fuction_on = true;        
        dccBasicParser.read_stream("<F 16 6 0>\n");
        CHECK(_fuction_lok_id == 16);
        CHECK(_fuction_function_number == 6);
        CHECK(!_fuction_on);
        CHECK(commandResult == "<X>\n");
    }
}