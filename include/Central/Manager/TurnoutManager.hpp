#ifndef __CENTRAL_TURNOUT_MANAGER_HPP__
#define __CENTRAL_TURNOUT_MANAGER_HPP__

#include <mutex>
#include <unordered_map>
#include <vector>
#include <DccExParser/TurnoutInterface.hpp>
#include <Common/TurnoutCache.hpp>
#include <DccProtocol/DccCommandGenerator.hpp>

namespace Central
{
    class TurnoutManager : public DccExParser::TurnoutInterface
    {
        public:
            TurnoutManager(std::mutex& main_track_mutex, DccProtocol::DccCommandGenerator& dcc_CommandGenerator);

            // Remove the Turnout
            void removeTurnout(int Id) override;

            // The status od this map is Throw, for all sensors
            // Status: 1: Close 0: Throw
            const std::unordered_map<int, bool> getTurnoutSensors() override;

            void statusTurnoutClose(int Id, bool state)  override;

            // Status: 0: Close 1: Throw
            void statusTurnoutThrow(int Id, bool state)  override;

            //
            void createTurnout(int Id, int Address, int SubAddress) override;

            //
            void createTurnout(int Id, int Address)  override;

            void createTurnout(const Common::Turnout& other);

            // Status: 0: Close 1: Throw
            void updateStatusByPin(int Pin, bool state);

            const std::vector<Common::Turnout> GetTurnoutVector();

        private:

            // mutex to access to the main staff
            std::mutex& main_track_mutex;
            DccProtocol::DccCommandGenerator& dcc_CommandGenerator;

            //
            std::mutex turnout_cache_mutex;
            Common::TurnoutCache m_TurnoutCache;
    };
}

#endif
