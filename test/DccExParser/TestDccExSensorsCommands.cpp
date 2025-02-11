#include <catch2/catch_test_macros.hpp>

#include "TestDccExHelpers.hpp"
#include "DccExCommadConverter.hpp"
#include "CommandInterface.hpp"

TEST_CASE("Test DCC Sensor commands")
{
    using namespace DccExParser;

    static std::string info_string;

    std::string commandResult;
    DccExParser::string_function_type commandFunction = [&commandResult](const std::string& command_result)
    {
        commandResult = command_result;
    };

    // helper variables to to tests sensors
    static int _countSensors_num = 0;
    static int _addSensor_sensorId = 0;
    static int _addSensor_virtualPin = 0;
    static bool _addSensor_isPullUp = false;
    static int _removeSensor_sensorId = 0;
    static int _getStatusSensor_sensorId = 0;
    static bool _getStatusSensor_Status = false;
    static int  _setStatusSensor_sensorId = 0;
    static bool _setStatusSensor_Status = false;
    static std::unordered_map<int, bool> _getStatusSensors_map = {};
    static std::unordered_map<int, std::pair<int, bool>> _getConfigurationSensors_map = {};

    class TestSensorsInterface : public SensorsInterface
    {
        virtual int countSensors()
        {
            return _countSensors_num;
        }

        virtual void addSensor(int id, int virtualPin, bool isPullUp)
        {
            _addSensor_sensorId = id;
            _addSensor_virtualPin = virtualPin;
            _addSensor_isPullUp = isPullUp;
        }

        virtual void removeSensor(int sensorId)
        {
            _removeSensor_sensorId = sensorId;
        }

        virtual bool getStatusSensor(int sensorId)
        {
            _getStatusSensor_sensorId = sensorId;
            return _getStatusSensor_Status;
        }

        virtual void setStatusSensor(int sensorId, bool Status)
        {
            _setStatusSensor_sensorId = sensorId;
            _setStatusSensor_Status= Status;
        }

        virtual const std::unordered_map<int, bool> getStatusSensors()
        {
            return _getStatusSensors_map;
        }

        virtual const std::unordered_map<int, std::pair<int, bool>> getConfigurationSensors()
        {
            return _getConfigurationSensors_map;
        }
    };

    // Create the basic variables to testing.
    TestMockLocoInterface  _TestMockLocoInterface;
    TestMockTrackInterface _TestMockTrackInterface;
    TestSensorsInterface _TestMockSensorsInterface;
    TestMockTurnoutInterface _TestMockTurnoutInterface;
    TestMockInfoInterface _TestMockInfoInterface;
    TestMockAccessoryInterface _TestMockAccessoryInterface;
    TestMockDccTrackInterface _TestMockDccTrackInterface;

    TestMockCommandManager _TestMockCommandManager(_TestMockLocoInterface, _TestMockTrackInterface, _TestMockSensorsInterface, _TestMockTurnoutInterface, _TestMockInfoInterface, _TestMockAccessoryInterface, _TestMockDccTrackInterface);

    DccExCommandParser dccParser(_TestMockCommandManager, commandFunction);
    DCCBasicParser dccBasicParser(dccParser);

    SECTION("Test Sensors Status")
    {
        _getStatusSensors_map = {std::pair(1 ,true), std::pair(2 ,false), std::pair(256 ,true)};
        dccBasicParser.read_stream("<Q>\n");
        CHECK(commandResult.find("<Q 1>\n") != std::string::npos);
        CHECK(commandResult.find("<q 2>\n") != std::string::npos);
        CHECK(commandResult.find("<Q 256>\n") != std::string::npos);
    }

    SECTION("Test Add Sensor")
    {
        _addSensor_sensorId = 0;
        _addSensor_virtualPin = 0;
        _addSensor_isPullUp = false;
        dccBasicParser.read_stream("<S 10 256 1>\n");
        CHECK(commandResult == "<O>\n");

        CHECK(_addSensor_sensorId == 10);
        CHECK(_addSensor_virtualPin == 256);
        CHECK(_addSensor_isPullUp);

        dccBasicParser.read_stream("<S 4 56 0>\n");
        CHECK(commandResult == "<O>\n");
        CHECK(_addSensor_sensorId == 4);
        CHECK(_addSensor_virtualPin == 56);
        CHECK(!_addSensor_isPullUp);
    }

    SECTION("Test Remove Sensor")
    {
        _removeSensor_sensorId = 0;
        dccBasicParser.read_stream("<S 5>\n");
        CHECK(commandResult == "<O>\n");
        CHECK(_removeSensor_sensorId == 5);
    }

    SECTION("Sensor Configuration")
    {
        _getConfigurationSensors_map = {{1 , std::pair(1, true)}, {10 , std::pair(2, false)} };
        dccBasicParser.read_stream("<S>\n");
        CHECK(commandResult.find("<Q 1 1 1>\n") != std::string::npos);
        CHECK(commandResult.find("<Q 10 2 0>\n") != std::string::npos);
    }
}
