#ifndef __RASPBERRY_PROGRAMMING_TRACK_HPP__
#define __RASPBERRY_PROGRAMMING_TRACK_HPP__

#include <DccProgrammingInterface.hpp>

class ProgrammingTrack : public DccProgrammingInterface
{
    public:
        ProgrammingTrack(int PowerPin, int EnablePin, int SignalPin):
            m_PowerPin(PowerPin), m_EnablePin(EnablePin), m_SignalPin(SignalPin)
        {}

    private:
        virtual unsigned char SendToDCCWithAck(const std::vector<unsigned char>& buffer, bool isWriteCommand);

        int m_PowerPin;
        int m_EnablePin;
        int m_SignalPin;
};

#endif
