#include "CentralManager.hpp"

namespace Central
{
    void CentralManager::setAccessory(int address, bool activate)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    
    }

    void CentralManager::setAccessory(int address, int subaddress, bool activate)
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    void CentralManager::setAccessory(int address, int subaddress, bool activate, bool onOff)
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    int CentralManager::getCurrentOnMain()
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    int CentralManager::getCurrentOnProg()
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    int CentralManager::getMaxCurrent()
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    void CentralManager::writeCVByteMain(int cab, int cv, char value)
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    void CentralManager::writeCVBitMain(int cab, int cv, int position, bool value)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::writeByteOnMain(std::vector<char> values)
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    void CentralManager::writeByteOnProg(std::vector<char> values)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::writeCVByte(int cv, char value)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::setLocoId(int cv)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::verifyCVBit(int cv, int position, bool value)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::writeCVBit(int cv, int position, bool value)
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    int CentralManager::getLocoId()
    {
        std::lock_guard<std::mutex> guard(access_mutex);


    }

    int CentralManager::readCV(int cv)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::verifyCVByte(int cv, char value)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    const std::string& CentralManager::getAdditionVersionInfo()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::getMaxLocos()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::setFunction(int cab, int function_number, bool on)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::updateFunction(int cab, int function_number)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    int CentralManager::searchLoco(int cab)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::createLoco(int cab, int locoId)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::removeLoco(int locoId)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::removeAllLocos()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::emergencyStopLoco(int locoId)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::emergencyStop()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::setLoco(int cab, int tspeed, bool forwardDirection)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::getLoco(int cab, int& locoId ,int& tspeed, long& functions)
    {
        std::lock_guard<std::mutex> guard(access_mutex);

    }

    int CentralManager::countSensors()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::addSensor(int sensorId, int virtualPin, bool isPullUp)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::removeSensor(int sensorId)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::getStatusSensor(int sensorId)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::setStatusSensor(int sensorId, bool Status)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    const std::unordered_map<int, bool> CentralManager::getStatusSensors()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    const std::unordered_map<int, std::pair<int, bool>> CentralManager::getConfigurationSensors()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::isTrackEnabled(TackType eTrack)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    bool CentralManager::isTrackOn(TackType eTrack)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::turnOnTrack(TackType eTrack)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::turnOffTrack(TackType eTrack)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::removeTurnout(int sensorId)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    const std::unordered_map<int, bool> CentralManager::getTurnoutSensors()
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::statusTurnoutClose(int sensorId, bool state)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::statusTurnoutThrow(int sensorId, bool state)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::createTurnout(int turnoutId, int address, int subAddress)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
    }

    void CentralManager::createTurnout(int turnoutId, int address)
    {
        std::lock_guard<std::mutex> guard(access_mutex);
/*
        turnout_cache.insert()
        void insert(Turnout turnout)
            {
                m_TurnoutCache.insert(turnout);
            }
        */
    }
}