#include "Mananger/TurnoutManager.hpp"
#include "Common/Turnout.hpp"

namespace Central
{
    TurnoutManager::TurnoutManager(
            std::mutex& main_track_mutex,
            DccProtocol::DccCommandGenerator& dcc_CommandGenerator) :
       main_track_mutex(main_track_mutex),
       dcc_CommandGenerator(dcc_CommandGenerator)
    {}

    void TurnoutManager::removeTurnout(int Id)
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        m_TurnoutCache.RemoveTurnoutById(Id);
    }

    const std::unordered_map<int, bool> TurnoutManager::getTurnoutSensors()
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        return m_TurnoutCache.getStatus();
    }

    void TurnoutManager::statusTurnoutClose(int Id, bool state)
    {
        int Address = 0;
        int subAddress = 0;
        {
            const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
            auto TurnoutCache = m_TurnoutCache.GetTurnoutById(Id);
            Address = TurnoutCache->Address;
            subAddress =  TurnoutCache->SubAddress;
            if (TurnoutCache->Status == StatusTurnout::Close)
            {
                LOG(DEBUG) << "Id: " << Id << "Address: " << Address << ", SubAddress: " << subAddress << ", Status: Close";
                return;
            }

            TurnoutCache->Status = StatusTurnout::Close;
        }

        LOG(DEBUG) << "Id: " << Id << "Address: " << Address << ", SubAddress: " << subAddress << ", Status: Close => Send Command";

        {
            const std::lock_guard<std::mutex> lock_cache(main_track_mutex);
            if (subAddress == 0)
            {
                dcc_CommandGenerator.SetAccessory(Address, true);
            }
            else
            {
                dcc_CommandGenerator.SetAccessory(Address, subAddress, true);
            }
        }
    }

    void TurnoutManager::statusTurnoutThrow(int Id, bool state)
    {
        int Address = 0;
        int subAddress = 0;
        {
            const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
            auto TurnoutCache = m_TurnoutCache.GetTurnoutById(Id);
            Address = TurnoutCache->Address;
            subAddress =  TurnoutCache->SubAddress;
            if (TurnoutCache->Status == StatusTurnout::Throw)
            {
                LOG(DEBUG) << "Id: " << Id << "Address: " << Address << ", SubAddress: " << subAddress << ", Status: Throw";
                return;
            }
            TurnoutCache->Status = StatusTurnout::Throw;
        }

        LOG(DEBUG) << "Id: " << Id << "Address: " << Address << ", SubAddress: " << subAddress << ", Status: Throw => Send Command";

        {
            const std::lock_guard<std::mutex> lock_cache(main_track_mutex);
            if (subAddress == 0)
            {
                dcc_CommandGenerator.SetAccessory(Address, false);
            }
            else
            {
                dcc_CommandGenerator.SetAccessory(Address, subAddress, false);
            }
        }
    }

    void TurnoutManager::createTurnout(int Id, int Address, int SubAddress)
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        m_TurnoutCache.Insert({.Id = Id, .Address = Address, .SubAddress = SubAddress});
    }

    void TurnoutManager::createTurnout(int Id, int Address)
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        m_TurnoutCache.Insert({.Id = Id, .Address = Address});
    }

    void TurnoutManager::createTurnout(const Common::Turnout& other)
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        m_TurnoutCache.Insert(other);
    }

    // Status: 0: Close 1: Throw
    void TurnoutManager::updateStatusByPin(int Pin, bool State)
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        m_TurnoutCache.SetStatusByPin(Pin, State);
    }

    const std::vector<Common::Loco> TurnoutManager::GetTurnoutVector()
    {
        const std::lock_guard<std::mutex> lock_cache(turnout_cache_mutex);
        return m_TurnoutCache.TurnoutVector();
    }
}