#ifndef __DCC_EX_TEST_CLASSES_HELPERS_HPP__
#define __DCC_EX_TEST_CLASSES_HELPERS_HPP__

#include "CommandInterface.hpp"

using namespace DccExParser;

class TestMockCommandManager: public CommandInterface
{
    public:
        
        TestMockCommandManager(
            LocoInterface& _locoInterface,
            TrackInterface& _trackInterface,
            SensorsInterface& _sensors,
            TurnoutInterface& _turnout,
            InfoInterface& _info
        ):
            _locoInterface(_locoInterface),
            _trackInterface(_trackInterface),
            _sensors(_sensors),
            _turnout(_turnout),
            _info(_info)
        {}

        LocoInterface& getLocosInfo()
        {
            return _locoInterface;
        }

        TrackInterface& getTrackInterface()
        {
            return _trackInterface;
        }
    
        SensorsInterface& getSensors()
        {
            return _sensors;
        }
        
        TurnoutInterface& getTurnout()
        {
            return _turnout;
        }
        
        InfoInterface& getInfo()
        {
            return _info;
        }

    private:
        LocoInterface& _locoInterface;
        TrackInterface& _trackInterface;
        SensorsInterface& _sensors;
        TurnoutInterface& _turnout;
        InfoInterface& _info;
};

class TestMockLocoInterface : public LocoInterface
{
    public:
        virtual int getMaxLocos()
        {
            return 0;
        }

        virtual void setFunction(int lok_id, int function_number, bool on)
        {
            return;
        }
        
        virtual int lookupLoco(int locoId)
        {
            return 0;
        }
        
        virtual bool createLoco(int locoId)
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
        {
            return;
        }

        virtual void turnOffTrack(TrackInterface::TackType _type)
        {
            return;
        }
};

class TestMockSensorsInterface : public SensorsInterface
{

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
};

class TestMockInfoInterface : public InfoInterface
{
    virtual const std::string& getAdditionVersionInfo()
    {
        static const std::string empty;
        return empty;
    }
};

#endif
