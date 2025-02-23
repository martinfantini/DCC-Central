#ifndef __DCC_EX_TEST_CLASSES_HELPERS_HPP__
#define __DCC_EX_TEST_CLASSES_HELPERS_HPP__

#include "CommandInterface.hpp"
#include "DccExCommandConverter.hpp"

using namespace DccExParser;

class TestMockCommandManager: public CommandInterface
{
    public:

        TestMockCommandManager(
            LocoInterface& _locoInterface,
            TrackInterface& _trackInterface,
            SensorsInterface& _sensors,
            TurnoutInterface& _turnout,
            InfoInterface& _info,
            AccessoryInterface& _accessoryInterface,
            DccTrackInterface&  _track
        ):
            _locoInterface(_locoInterface),
            _trackInterface(_trackInterface),
            _sensors(_sensors),
            _turnout(_turnout),
            _info(_info),
            _accessoryInterface(_accessoryInterface),
            _track(_track)
        {}

        LocoInterface& getLocosInterface()
        {
            return _locoInterface;
        }

        TrackInterface& getTrackInterface()
        {
            return _trackInterface;
        }
    
        SensorsInterface& getSensorsInterface()
        {
            return _sensors;
        }

        TurnoutInterface& getTurnoutInterface()
        {
            return _turnout;
        }

        InfoInterface& getInfoInterface()
        {
            return _info;
        }

        AccessoryInterface& getAccessoryInterface()
        {
            return _accessoryInterface;
        }

        DccTrackInterface&  getDccTrackInterface()
        {
            return _track;
        }

    private:
        LocoInterface& _locoInterface;
        TrackInterface& _trackInterface;
        SensorsInterface& _sensors;
        TurnoutInterface& _turnout;
        InfoInterface& _info;
        AccessoryInterface& _accessoryInterface;
        DccTrackInterface& _track;
};

class TestMockLocoInterface : public LocoInterface
{
    public:
        virtual int getMaxLocos()
        {
            return 0;
        }

        virtual bool setFunction(int lok_id, int function_number, bool on)
        {
            return true;
        }

        virtual void updateFunction(int cab, int function_number)
        {}

        virtual int searchLoco(int cab)
        {
            return 0;
        }

        virtual bool createLoco(int cab, int locoId)
        {
            return true;
        }

        virtual void removeLoco(int)
        {}

        virtual void removeAllLocos()
        {}

        virtual void emergencyStopLoco(int)
        {}

        virtual void emergencyStop()
        {}

        virtual bool setLoco(int cab, int tspeed, bool forwardDirection)
        {
            return true;
        }

        virtual bool getLoco(int cab, int& locoId ,int& tspeed, int& functions)
        {
            return true;
        }
};

class TestMockTrackInterface : public TrackInterface
{
    public:
        virtual bool isTrackEnabled(TrackInterface::TackType _type)
        {
            return true;
        }

        virtual bool isTrackOn(TrackInterface::TackType _type)
        {
            return true;
        }

        virtual void turnOnTrack(TrackInterface::TackType _type)
        {}

        virtual void turnOffTrack(TrackInterface::TackType _type)
        {}
};

class TestMockSensorsInterface : public SensorsInterface
{
    public:
        virtual int countSensors()
        {
            return 0;
        }

        virtual void addSensor(int sensorId, int virtualPin, bool isPullUp)
        {}

        virtual void removeSensor(int sensorId)
        {}

        virtual bool getStatusSensor(int sensorId)
        {
            return true;
        }

        virtual void setStatusSensor(int sensorId, bool Status)
        {}

        virtual const std::unordered_map<int, bool> getStatusSensors()
        {
            return {};
        }

        virtual const std::unordered_map<int, std::pair<int, bool>> getConfigurationSensors()
        {
            return {};
        }
};

class TestMockTurnoutInterface : public TurnoutInterface
{
    public:
        virtual void removeTurnout(int sensorId)
        {}

        virtual const std::unordered_map<int, bool> getTurnoutSensors()
        {
            return {};
        }

        virtual void statusTurnoutClose(int sensorId, bool state)
        {}

        virtual void statusTurnoutThrow(int sensorId, bool state)
        {}

        virtual void createTurnout(int turnoutId, int address, int subAddress)
        {}

        virtual void createTurnout(int turnoutId, int address)
        {}

};

class TestMockInfoInterface : public InfoInterface
{
    public:
        virtual const std::string& getAdditionVersionInfo()
        {
            static const std::string empty;
            return empty;
        }
};

class TestMockDccTrackInterface : public DccTrackInterface
{
    public:
        virtual int getCurrentOnMain()
        {
            return 0;
        }

        virtual int getCurrentOnProg()
        {
            return 0;
        }

        virtual int getMaxCurrent()
        {
            return 0;
        }

        virtual void writeCVByteMain(int cab, int cv, char value)
        {}

        virtual void writeCVBitMain(int cab, int cv, int position, bool value)
        {}

        virtual void writeByteOnMain(std::vector<char> values)
        {}

        virtual void writeByteOnProg(std::vector<char> values)
        {}

        virtual int writeCVByte(int cv, char value)
        {
            return 0;
        }

        virtual int setLocoId(int cv)
        {
            return 0;
        }

        virtual int verifyCVBit(int cv, int position, bool value)
        {
            return 0;
        }

        virtual int writeCVBit(int cv, int position, bool value)
        {
            return 0;
        }

        virtual int getLocoId()
        {
            return 0;
        }

        virtual int readCV(int cv)
        {
            return 0;
        }

        virtual int verifyCVByte(int cv, char value)
        {
            return 0;
        }
};

class TestMockAccessoryInterface : public AccessoryInterface
{
    public:
        virtual void setAccessory(int address, bool activate)
        {}

        virtual void setAccessory(int address, int subaddress, bool activate)
        {}

        virtual void setAccessory(int address, int subaddress, bool activate, bool onOff)
        {}
};

class DccExResponse : public DccExCommandResponse
{
    public:
        DccExResponse(std::string& response, bool append = false):
            commandResult(response),
            append(append)
        {}

        virtual void send_response(const std::string& response)
        {
            if (append)
                commandResult += response;
            else
                commandResult = response;
        }

    private:
        std::string& commandResult;
        bool append = false;
};
#endif
