#include "Mananger/AccessoryManager.hpp"

#include <glog/logging.h>

namespace Central
{
    void AccessoryManager::UpdateAccessoryMap(Common::Accessory accessory)
    {
        {
            const std::lock_guard<std::mutex> lock(accessory_set_mutex);
            auto result = AccessorySet.find(accessory)
            if (result ==  AccessorySet.end())
            {
                AccessorySet.insert(accessory);
            }
            else
            {
                AccessorySet.erase(result);
                AccessorySet.insert(accessory);
            }
        }
    }

    void AccessoryManager::setAccessory(int address, bool activate)
    {
        LOG(DEBUG) << "Address: " << address << " , Activate: " << std::boolalpha <<  activate;

        UpdateAccessoryMap({ .Address=address, .isActive=activate})

        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetAccessory(address, activate);
        }
    }

    void AccessoryManager::setAccessory(int address, int subaddress, bool activate)
    {
        if (subaddress < 1 || subaddress > 4)
        {
            LOG(ERROR) << "Address: " << address << " , Sub Address: " << subaddress << " not in range 1-4";
            return;
        }

        LOG(DEBUG) << "Address: " << address << ", SubAddress: " << subaddress <<", Activate: " << std::boolalpha <<  activate;

        UpdateAccessoryMap({ .Address=address, .SubAddress=subaddress, .isActive=activate})

        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetAccessory(address, subaddress, activate);
        }
    }

    void AccessoryManager::setAccessory(int address, int subaddress, bool activate, bool onOff)
    {
        if (subaddress < 1 || subaddress > 4)
        {
            LOG(ERROR) << "Address: " << address << " , Sub Address: " << subaddress << " not in range 1-4";
            return;
        }

        LOG(DEBUG) << "Address: " << address << ", SubAddress: " << subaddress <<", Activate: " << std::boolalpha <<  activate << " onOff: " << std::boolalpha <<  onOff;

        UpdateAccessoryMap({ .Address=address, .SubAddress=subaddress , .isActive=activate, .isOn=onOff})

        {
            const std::lock_guard<std::mutex> lock(main_track_mutex);
            dcc_CommandGenerator.SetAccessory(address, subaddress, activate, onOff);
        }
    }

    AccessoryManager::AccessoryManager(std::mutex &main_track_mutex, DccCommandGenerator& dcc_CommandGenerator) :
        main_track_mutex(main_track_mutex),
        dcc_CommandGenerator(dcc_CommandGenerator)
    {}

    const Accessory_Set_Type& AccessoryManager::getAccessorySet()
    {
        const std::lock_guard<std::mutex> lock(accessory_set_mutex);
        return AccessorySet;
    }

    const std::pair<bool,Accessory> AccessoryManager::getAccessory(int address, int subaddress)
    {
        const std::lock_guard<std::mutex> lock(accessory_set_mutex);
        auto found = AccessorySet.find({ .Address=address, .SubAddress=subaddress});
        if (found == AccessorySet.end())
            return {false, { .Address=address, .SubAddress=subaddress} };
        return {true, *found}
    }
}
