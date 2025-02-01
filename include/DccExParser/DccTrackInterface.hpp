#ifndef __DCC_EX_DCC_TRACK_INTERFACE_HPP__
#define __DCC_EX_DCC_TRACK_INTERFACE_HPP__

#include<vector>

namespace DccExParser
{
    class DccTrackInterface
    {
        public:
            // Both data are in milliampere
            virtual int getCurrentOnMain() = 0;
            virtual int getCurrentOnProg() = 0;
            virtual int getMaxCurrent() = 0;

            // To Write Byte/Bit on track
            virtual void writeCVByteMain(int cab, int cv, char value) = 0;
            virtual void writeCVBitMain(int cab, int cv, int position, bool value) = 0;

            // To direct write on Main/Prog track
            virtual void writeByteOnMain(std::vector<char> values) = 0;
            virtual void writeByteOnProg(std::vector<char> values) = 0;

            // ***
            // To Write / Read Data on Prog Track
            // ***
            // Verify Data. / Read
            virtual int writeCVByte(int cv, char value) = 0;
            virtual int setLocoId(int cv) = 0;
            virtual int verifyCVBit(int cv, int position, bool value) = 0;
            virtual int writeCVBit(int cv, int position, bool value) = 0;
            virtual int getLocoId() = 0;
            virtual int readCV(int cv) = 0;
            virtual int verifyCVByte(int cv, char value) = 0;
    };
}
#endif