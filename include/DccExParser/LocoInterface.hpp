#ifndef __DCC_EX_LOCO_INTERFACE_HPP__
#define __DCC_EX_LOCO_INTERFACE_HPP__

namespace DccExParser
{
    class LocoInterface
    {
        public:
            // return the maximum m number of locos
            virtual int getMaxLocos() = 0;
            // to set a function in a loco
            virtual bool setFunction(int cab, int function_number, bool on) = 0;
            // to update a loco
            virtual void updateFunction(int cab, int function_number) = 0;
            //
            virtual int searchLoco(int cab) = 0;
            // Add new loco
            virtual bool createLoco(int cab, int locoId) = 0;
            // Remove loco by id
            virtual void removeLoco(int locoId) = 0;
            // Remove all locos
            virtual void removeAllLocos() = 0;
            // Emergency stop a loco
            virtual void emergencyStopLoco(int locoId) = 0;
            // Emergency all locos
            virtual void emergencyStop() = 0;
            // to set the values of an actual loco
            virtual bool setLoco(int cab, int tspeed, bool forwardDirection) = 0;
            // to get the data from a loco, internal value
            virtual bool getLoco(int cab, int& locoId ,int& tspeed, long& functions) = 0;

            virtual ~LocoInterface(){}
    };
}
#endif