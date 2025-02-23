#ifndef __CENTRAL_DCC_COMMAND_MANAGER_HPP__
#define __CENTRAL_DCC_COMMAND_MANAGER_HPP__

#include "LocosManager.hpp"
#include "TrackManager.hpp"
#include "SensorsManager.hpp"
#include "TurnoutManager.hpp"
#include "InfoManager.hpp"
#include "AccessoryManager.hpp"
#include "DccTrackManager.hpp"

#include <DccExParser/CommandInterface.hpp>
#include <DccProtocol/DccCommandGenerator.hpp>
#include <DccProtocol/DccProgrammingCommandGenerator.hpp>

#include<mutex>

namespace Central
{
    class DccCommandManager: public DccExParser::CommandInterface
    {
        public:
            DccCommandManager(DccCommandGenerator& dcc_CommandGenerator, DccProgrammingCommandGenerator& dcc_ProgrammingCommandGenerator):
            {
                m_LocosManager = LocosManager(main_track_mutex, dcc_CommandGenerator);
                m_TrackManager = TrackManager(main_track_mutex, programming_track_mutex);
                m_SensorsManager = SensorsManager();
                m_TurnoutManager = TurnoutManager(main_track_mutex);
                m_InfoManager = InfoManager();
                m_AccessoryManager = AccessoryManager(main_track_mutex, dcc_CommandGenerator);
                m_DccTrackManager = DccTrackManager(main_track_mutex, programming_track_mutex);
            }

            LocosManager& getLocosInterface() override
            {
                return m_LocosManager;
            }

            TrackManager& getTrackInterface() override
            {
                return m_TrackManager;
            }

            SensorsManager& getSensorsInterface() override
            {
                return m_SensorsManager;
            }

            TurnoutManager& getTurnoutInterface() override
            {
                return m_TurnoutManager;
            }

            InfoManager& getInfoInterface() override
            {
                return m_InfoManager;
            }

            AccessoryManager& getAccessoryInterface() override
            {
                return m_AccessoryManager;
            }

            DccTrackManager& getDccTrackInterface() override
            {
                return m_DccTrackManager;
            }

        private:

            // mutex to access to the main staff
            std::mutex main_track_mutex;
            // mutex to access to the progarming staff
            std::mutex programming_track_mutex;

            //All the managers
            LocosManager m_LocosManager;
            TrackManager m_TrackManager;
            SensorsManager m_SensorsManager;
            TurnoutManager m_TurnoutManager;
            InfoManager m_InfoManager;
            AccessoryManager m_AccessoryManager;
            DccTrackManager  m_DccTrackManager;
    }
};

#endif