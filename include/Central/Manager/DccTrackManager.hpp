#ifndef __CENTRAL_DCC_TRACK_MANAGER_HPP__
#define __CENTRAL_DCC_TRACK_MANAGER_HPP__

#include<mutex>

#include <DccExParser/DccTrackInterface.hpp>

namespace Central
{
    class DccTrackManager : public DccExParser::DccTrackInterface
    {
        public:

            DccTrackManager(std::mutex& main_track_mutex, std::mutex& programming_track_mutex);

            // Both data are in milliampere
            int getCurrentOnMain() override;
            int getCurrentOnProg() override;
            int getMaxCurrent() override;

            // To Write Byte/Bit on track
            void writeCVByteMain(int cab, int cv, char value) override;
            void writeCVBitMain(int cab, int cv, int position, bool value) override;

            // To direct write on Main/Prog track
            void writeByteOnMain(std::vector<char> values) override;
            void writeByteOnProg(std::vector<char> values) override;

            // ***
            // To Write / Read Data on Prog Track
            // ***
            // Verify Data. / Read
            int writeCVByte(int cv, char value) override;
            int setLocoId(int cv) override;
            int verifyCVBit(int cv, int position, bool value) override;
            int writeCVBit(int cv, int position, bool value) override;
            int getLocoId() override;
            int readCV(int cv) override;
            int verifyCVByte(int cv, char value) override;

        private:
            // mutex to access to the main staff
            std::mutex& main_track_mutex;
            // mutex to access to the progarming staff
            std::mutex& programming_track_mutex;
    };
}

#endif
