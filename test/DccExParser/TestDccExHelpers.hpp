#ifndef __DCC_EX_TEST_CLASSES_HELPERS_HPP__
#define __DCC_EX_TEST_CLASSES_HELPERS_HPP__

#include "CommandInterface.hpp"

using namespace DccExParser;

class TestMockCommandManager: public CommandInterface
{
    public:
        
        TestMockCommandManager(LocoInterface& _locoInterface, TrackInterface& _trackInterface):
            _locoInterface(_locoInterface),
            _trackInterface(_trackInterface)
        {}

        LocoInterface& getLocosInfo()
        {
            return _locoInterface;
        }

        TrackInterface& getTrackInterface()
        {
            return _trackInterface;
        }
    
    private:
        LocoInterface& _locoInterface;
        TrackInterface& _trackInterface;
};

class TestMockLocoInterface : public LocoInterface
{
    public:
        int getMaxLocos()
        {
            return 0;
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

class TestMockTrackInterface : public TrackInterface
{
    public:
        bool isTrackEnabled(TrackInterface::TackType _type)
        {
            return true;
        }
        bool isTrackOn(TrackInterface::TackType _type)
        {
            return true;
        }

        void turnOnTrack(TrackInterface::TackType _type)
        {
            return;
        }

        void turnOffTrack(TrackInterface::TackType _type)
        {
            return;
        }
};

#endif