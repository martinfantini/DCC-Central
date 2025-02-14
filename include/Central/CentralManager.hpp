#ifndef __CENTRAL_CENTRAL_MANAGER_HPP__
#define __CENTRAL_CENTRAL_MANAGER_HPP__

#include <DccExParser/AccessoryInterface.hpp>
#include <DccExParser/DccTrackInterface.hpp>
#include <DccExParser/InfoInterface.hpp>
#include <DccExParser/LocoInterface.hpp>
#include <DccExParser/SensorsInterface.hpp>
#include <DccExParser/TrackInterface.hpp>
#include <DccExParser/TurnoutInterface.hpp>

#include <Common/Accessory.hpp>
#include <Common/LocoCache.hpp>
#include <Common/SensorCache.hpp>
#include <Common/TurnoutCache.hpp>

#include <mutex>

namespace Central
{
    class CentralManager: 
        public DccExParser::AccessoryInterface,
        public DccExParser::DccTrackInterface,
        public DccExParser::InfoInterface,
        public DccExParser::LocoInterface,
        public DccExParser::SensorsInterface,
        public DccExParser::TrackInterface,
        public DccExParser::TurnoutInterface
    {
        public:
            virtual void setAccessory(int address, bool activate);
            virtual void setAccessory(int address, int subaddress, bool activate);
            virtual void setAccessory(int address, int subaddress, bool activate, bool onOff);

            virtual int getCurrentOnMain();
            virtual int getCurrentOnProg();
            virtual int getMaxCurrent();

            virtual void writeCVByteMain(int cab, int cv, char value);
            virtual void writeCVBitMain(int cab, int cv, int position, bool value);

            virtual void writeByteOnMain(std::vector<char> values);
            virtual void writeByteOnProg(std::vector<char> values);

            virtual int writeCVByte(int cv, char value);
            virtual int setLocoId(int cv);
            virtual int verifyCVBit(int cv, int position, bool value);
            virtual int writeCVBit(int cv, int position, bool value);
            virtual int getLocoId();
            virtual int readCV(int cv);
            virtual int verifyCVByte(int cv, char value);

            virtual const std::string& getAdditionVersionInfo();

            virtual int getMaxLocos();
            virtual bool setFunction(int cab, int function_number, bool on);
            virtual void updateFunction(int cab, int function_number);
            virtual int searchLoco(int cab);
            virtual bool createLoco(int cab, int locoId);
            virtual void removeLoco(int locoId);
            virtual void removeAllLocos();
            virtual void emergencyStopLoco(int locoId);
            virtual void emergencyStop();
            virtual bool setLoco(int cab, int tspeed, bool forwardDirection);
            virtual bool getLoco(int cab, int& locoId ,int& tspeed, long& functions);

            virtual int countSensors();
            virtual void addSensor(int sensorId, int virtualPin, bool isPullUp);
            virtual void removeSensor(int sensorId);
            virtual bool getStatusSensor(int sensorId);
            virtual void setStatusSensor(int sensorId, bool Status);
            virtual const std::unordered_map<int, bool> getStatusSensors();
            virtual const std::unordered_map<int, std::pair<int, bool>> getConfigurationSensors();

            virtual bool isTrackEnabled(TackType eTrack);
            virtual bool isTrackOn(TackType eTrack);
            virtual void turnOnTrack(TackType eTrack);
            virtual void turnOffTrack(TackType eTrack);

            virtual void removeTurnout(int sensorId);
            virtual const std::unordered_map<int, bool> getTurnoutSensors();
            virtual void statusTurnoutClose(int sensorId, bool state);
            virtual void statusTurnoutThrow(int sensorId, bool state);
            virtual void createTurnout(int turnoutId, int address, int subAddress);
            virtual void createTurnout(int turnoutId, int address);
        private:
            Common::Accessory_Set_Type  accessory_set;
            Common::LocoCache           loco_cache;
            Common::TurnoutCache        turnout_cache;
            Common::SensorCache         sensor_set;

            std::mutex access_mutex;
    };
}

#endif
