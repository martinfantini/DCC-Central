#ifndef __DCC_EX_LOCO_INTERFACE_HPP__
#define __DCC_EX_LOCO_INTERFACE_HPP__

namespace DccExParser
{
    class LocoInterface
    {
        public:
            virtual int getMaxLocos() = 0;
            virtual void setFunction(int lok_id, int function_number, bool on) = 0;
            virtual int lookupLoco(int locoId) = 0;
            virtual bool createLoco(int locoId) = 0;
            virtual void removeLoco(int locoId) = 0;
            virtual void removeAllLocos() = 0;
            virtual void emergencyStopLoco(int locoId) = 0;
            virtual void emergencyStop() = 0;
            virtual ~LocoInterface(){}
    };
}
#endif