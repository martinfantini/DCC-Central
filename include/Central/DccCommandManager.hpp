#ifndef __CENTRAL_DCC_COMMAND_MANAGER_HPP__
#define __CENTRAL_DCC_COMMAND_MANAGER_HPP__

#include <DccExParser/CommandInterface.hpp>

namespace Central
{
    class DccCommandManager: public DccExParser::CommandInterface
    {
        public:
            DccCommandManager(CentralManager& centralManager):
                m_CentralManager(centralManager)
            {}

            LocoInterface& getLocosInterface()
            {
                return m_CentralManager;
            }

            TrackInterface& getTrackInterface()
            {
                return m_CentralManager;
            }

            SensorsInterface& getSensorsInterface()
            {
                return m_CentralManager;
            }

            TurnoutInterface& getTurnoutInterface()
            {
                return m_CentralManager;
            }

            InfoInterface& getInfoInterface()
            {
                return m_CentralManager;
            }

            AccessoryInterface& getAccessoryInterface()
            {
                return m_CentralManager;
            }

            DccTrackInterface& getDccTrackInterface()
            {
                return m_CentralManager;
            }

        private:
            CentralManager& m_CentralManager;
    }
};

#endif