#ifndef __CENTRAL_ACCESSORY_MANAGER_HPP__
#define __CENTRAL_ACCESSORY_MANAGER_HPP__

#include<mutex>

#include <Common/Accessory.hpp>
#include <DccExParser/AccessoryInterface.hpp>
#include <utility>

namespace Central
{
    class AccessoryManager : public DccExParser::AccessoryInterface
    {
        public:
            AccessoryManager(std::mutex& main_track_mutex, DccProtocol::DccCommandGenerator& dcc_CommandGenerator);

            virtual void setAccessory(int address, bool activate) override;
            virtual void setAccessory(int address, int subaddress, bool activate)  override;
            virtual void setAccessory(int address, int subaddress, bool activate, bool onOff)  override;

            const Accessory_Set_Type& getAccessorySet();

            const std::pair<bool, Common::Accessory> getAccessory(int address, int subaddress = 0);

        private:
            std::mutex& main_track_mutex;

            std::mutex accessory_set_mutex;
            Common::Accessory_Set_Type  AccessorySet;

            void UpdateAccessoryMap(Common::Accessory accessory);

            DccProtocol::DccCommandGenerator& dcc_CommandGenerator;
    };
}

#endif
