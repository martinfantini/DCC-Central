#ifndef __DCC_EX_ACCESSORY_INTERFACE_HPP__
#define __DCC_EX_ACCESSORY_INTERFACE_HPP__

namespace DccExParser
{
    class AccessoryInterface
    {
        public:
            virtual void setAccessory(int address, bool activate) = 0;
            virtual void setAccessory(int address, int subaddress, bool activate) = 0;
            virtual void setAccessory(int address, int subaddress, bool activate, bool onOff) = 0;
    };
}

#endif
