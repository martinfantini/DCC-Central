#ifndef __CENTRAL_LOCO_MANAGER_HPP__
#define __CENTRAL_LOCO_MANAGER_HPP__

#include<mutex>

#include <Common/LocoCache.hpp>
#include <DccExParser/LocoInterface.hpp>
#include <DccProtocol/DccCommandGenerator.hpp>
#include <utility>

namespace Central
{
    class LocoManager: public DccExParser::LocoInterface
    {
        public:

            LocoManager(std::mutex& main_track_mutex, DccProtocol::DccCommandGenerator& dcc_CommandGenerator);

            void InsertLoco(const Common::Loco& loco);

            const std::vector<Common::Loco> GetLocoVector();

            const std::pair<bool, Common::Loco> GetLocoByAddress(int cab);

            const std::pair<bool, Common::Loco> GetLocoById(int locoId);

            void setMaxLocos(int MaxLocos)
            {
                m_MaxLocos = MaxLocos;
            }

            int getMaxLocos() override
            {
                return m_MaxLocos;
            }

            // to set a function in a loco
            bool setFunction(int cab, int function_number, bool on) override;

            // to update a loco
            void updateFunction(int cab, int function_number) override;

            //
            int searchLoco(int cab) override;

            // Add new loco
            bool createLoco(int cab, int locoId) override;

            // Remove loco by id
            void removeLoco(int locoId) override;

            // Remove all locos
            void removeAllLocos() override;

            // Emergency stop a loco
            void emergencyStopLoco(int locoId) override;

            // Emergency all locos
            void emergencyStop() override;

            // to set the values of an actual loco
            bool setLoco(int cab, int tspeed, bool forwardDirection) override;

            // to get the data from a loco, internal value
            bool getLoco(int cab, int& locoId ,int& tspeed, int& functions) override;

        private:
            // mutex to access to the main staff
            std::mutex& main_track_mutex;
            DccProtocol::DccCommandGenerator& dcc_CommandGenerator

            // All stored Locos
            Common::LocoCache m_LocoCache;

            // mutex to access to the map
            std::mutex loco_cache_mutex;

            int m_MaxLocos = 100;
    };
}

#endif
