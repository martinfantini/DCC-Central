
#include "Mananger/LocoManager.hpp"
#include "Common/LocoCache.hpp"

#include <glog/logging.h>

namespace Central
{

    using namespace Common;

    LocoManager::LocoManager(std::mutex& main_track_mutex, DccProtocol::DccCommandGenerator& dcc_CommandGenerator) :
        main_track_mutex(main_track_mutex),
        dcc_CommandGenerator(dcc_CommandGenerator)
    {}

    void LocoManager::InsertLoco(const Loco& loco)
    {
        const std::lock_guard<std::mutex> lock_cache(loco_cache_mutex);
        m_LocoCache.Insert(loco);
    }

    const std::vector<Loco> LocoManager::GetLocoVector()
    {
        const std::lock_guard<std::mutex> lock_cache(loco_cache_mutex);
        return m_LocoCache.LocoVector();
    }

    const std::pair<bool, Loco> LocoManager::GetLocoByAddress(int cab)
    {
        const std::lock_guard<std::mutex> lock_cache(loco_cache_mutex);
        auto result = m_LocoCache.GetLocoByAddress(cab);
        if (result == nullptr)
            return {false, {}};
        return {false, *result};
    }

    const std::pair<bool, Loco> LocoManager::GetLocoById(int locoId)
    {
        const std::lock_guard<std::mutex> lock_cache(loco_cache_mutex);
        auto result = m_LocoCache.GetLocoById(locoId);
        if (result == nullptr)
            return {false, {}};
        return {false, *result};
    }

    bool LocoManager::setFunction(int cab, int function_number, bool on)
    {
        const std::lock_guard<std::mutex> lock_cache(loco_cache_mutex);
        auto result = m_LocoCache.GetLocoByAddress(cab);
        if (result == nullptr)
        {
            LOG(ERROR) << "Not found loco by Address: " << cab << " in the map";
            return false;
        }

        if (!LocoHasFunction(*result.FunctionIndicator, function_number))
        {
            LOG(ERROR) << "Loco Address " << cab << " has not allowed this function " << function_number;
            return false;
        }

        LOG(DEBUG) << "Loco Address " << cab << ", function number: " << function_number << " , On " << std::alphabool << on;

        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetLocoFunction(cab, function_number, on, *result.FunctionStatus);
        }
    }

    void LocoManager::updateFunction(int cab, int function_number)
    {
        const std::lock_guard<std::mutex> lock(main_track_mutex);
        auto result = m_LocoCache.GetLocoByAddress(cab);
        if (result == nullptr)
            return 0;

        if ( function_number > LocoFunctionsGroup::LocoFunctionsGroup_None 
             && function_number < LocoFunctionsGroup::LocoFunctionsGroup_Max)
        {
            result.FunctionIndicator = (LocoFunctionsGroup) function_number;
        }

        LOG(DEBUG) << "Loco Address " << cab << ", function indicator: " << result.FunctionIndicator;
    }

    int LocoManager::searchLoco(int cab)
    {
        const std::lock_guard<std::mutex> lock(loco_cache_mutex);
        auto result = m_LocoCache.GetLocoByAddress(cab);
        if (result == nullptr)
            return 0;
        return result.Id;
    }

    bool LocoManager::createLoco(int cab, int locoId)
    {
        Common::Loco loco;
        loco.Id = locoId;
        loco.Address = cab;
        {
            const std::lock_guard<std::mutex> lock(loco_cache_mutex);
            m_LocoCache.Insert(loco);
        }
    }

    void LocoManager::removeLoco(int locoId)
    {
        const std::lock_guard<std::mutex> lock(loco_cache_mutex);
        m_LocoCache.RemoveLocoById(locoId);
    }

    void LocoManager::removeAllLocos()
    {
        const std::lock_guard<std::mutex> lock(loco_cache_mutex);
        m_LocoCache.ClearCache();
    }

    void LocoManager::emergencyStopLoco(int locoId)
    {
        LOG(DEBUG) << "Emergency Stop for LocoId: " << locoId;

        int Address = 0;
        {
            const std::lock_guard<std::mutex> lock(loco_cache_mutex);
            m_LocoCache.EmergencyStopById(locoId);
            auto result = m_LocoCache.GetLocoById(locoId);
            if (result == nullptr)
                return;
            Address = (*result).Address;
        }

        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetEmergencyStrop(Address)
        }
    }

    void LocoManager::emergencyStop()
    {
        LOG(DEBUG) << "Emergency Stop";
        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetEmergencyStrop();
        }

        {
            const std::lock_guard<std::mutex> lock(loco_cache_mutex);
            m_LocoCache.EmergencyStop();
        }

    }

    bool LocoManager::setLoco(int cab, int tspeed, bool forwardDirection)
    {
        int SpeedSteps = 0;
        {
            const std::lock_guard<std::mutex> lock(loco_cache_mutex);
            auto result = m_LocoCache.GetLocoByAddress(cab);
            if (result == nullptr)
                return false;

            result->Speed = tspeed;
            result->Direction = forwardDirection;
            SpeedSteps = result->SpeedSteps;
        }

        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetLocoSpeedDirection(cab, tSpeed, forwardDirection, SpeedSteps);
        }
    }

    bool LocoManager::getLoco(int cab, int& locoId ,int& tspeed, int& functions)
    {
        const std::lock_guard<std::mutex> lock(loco_cache_mutex);
        auto result = m_LocoCache.GetLocoByAddress(cab);
        if (result == nullptr)
            return false;

        locoId = result.Id;
        tspeed = result.Speed;
        functions = result.FunctionIndicator;
        return true;
    }
}
