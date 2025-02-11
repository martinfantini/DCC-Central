#ifndef __RASPBERRY_DMA_MAIN_TRACK_HPP__
#define __RASPBERRY_DMA_MAIN_TRACK_HPP__

#include <DccInterface.hpp>

namespace RaspberryDMA
{
    class MainTrack : public DccInterface
    {
        public:
            MainTrack(int PowerPin, int EnablePin, int SignalPin):
                m_PowerPin(PowerPin), m_EnablePin(EnablePin), m_SignalPin(SignalPin)
            {}

        private:
            virtual void SendToDCC(const std::vector<unsigned char>& buffer, int RepeatCommand = 0);

            int m_PowerPin;
            int m_EnablePin;
            int m_SignalPin;
    };
}

#endif
