#include "Mananger/AccessoryManager.hpp"

namespace Central
{

    DccTrackManager::DccTrackManager(std::mutex& main_track_mutex, std::mutex& programming_track_mutex):
        main_track_mutex(main_track_mutex), programming_track_mutex(programming_track_mutex)
    {}

    // Both data are in milliampere
    int DccTrackManager::getCurrentOnMain()
    {
        const std::lock_guard<std::mutex> lock(main_track_mutex);
    }

    int DccTrackManager::getCurrentOnProg()
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }
    
    int DccTrackManager::getMaxCurrent()
    {}

    // To Write Byte/Bit on track
    void DccTrackManager::writeCVByteMain(int cab, int cv, char value)
    {
        const std::lock_guard<std::mutex> lock(main_track_mutex);
    }

    void DccTrackManager::writeCVBitMain(int cab, int cv, int position, bool value)
    {
        const std::lock_guard<std::mutex> lock(main_track_mutex);
    }

    // To direct write on Main/Prog track
    void DccTrackManager::writeByteOnMain(std::vector<char> values)
    {
        const std::lock_guard<std::mutex> lock(main_track_mutex);
    }

    void DccTrackManager::writeByteOnProg(std::vector<char> values)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::writeCVByte(int cv, char value)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::setLocoId(int cv)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::verifyCVBit(int cv, int position, bool value)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::writeCVBit(int cv, int position, bool value)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::getLocoId()
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::readCV(int cv)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }

    int DccTrackManager::verifyCVByte(int cv, char value)
    {
        const std::lock_guard<std::mutex> lock(programming_track_mutex);
    }
}