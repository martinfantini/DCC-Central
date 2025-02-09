#ifndef __DCC_PROTOCOL_DCC_COMMAND_GENERATOR_HPP__
#define __DCC_PROTOCOL_DCC_COMMAND_GENERATOR_HPP__

#include "DccProgrammingInterface.hpp"

namespace DccProtocol
{
    /**
     * @brief This class generate all the corresponding data to be send in the wire
     * for the programming track, with the different commands available in the dcc
     * protocol specification.
     */

    class DccProgrammingCommandGenerator
    {
    public:
        DccProgrammingCommandGenerator(DccProgrammingInterface& DccProgrammingInterface):
            m_DccProgrammingInterface(DccProgrammingInterface)
        {}

        std::pair<bool, unsigned char> ReadCV(unsigned int CV);
        std::pair<bool, unsigned char> WriteCV(unsigned int CV, unsigned char Value);

        std::pair<bool, unsigned char> ReadCVBit(unsigned int CV, unsigned int BitPosition);
        std::pair<bool, unsigned char> WriteCVBit(unsigned int CV,  unsigned int BitPosition, unsigned char Value);

        bool WriteAddress(unsigned int Address);

    private:
        DccProgrammingInterface& m_DccProgrammingInterface;
    };
}

#endif