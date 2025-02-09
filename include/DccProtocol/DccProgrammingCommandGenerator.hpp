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
        DccProgrammingCommandGenerator(DccProgrammingInterface& _DccProgrammingInterface):
            _DccProgrammingInterface(_DccProgrammingInterface)
        {}

    private:
        DccProgrammingInterface& _DccProgrammingInterface;
    };
}

#endif