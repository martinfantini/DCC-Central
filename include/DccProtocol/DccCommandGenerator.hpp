#ifndef __DCC_PROTOCOL_DCC_COMMAND_GENERATOR_HPP__
#define __DCC_PROTOCOL_DCC_COMMAND_GENERATOR_HPP__

#include <vector>

#include "DccInterface.hpp"

namespace DccProtocol
{
    /**
     * @brief This class generate all the corresponding data to be send in the wire,
     * with the different commands available in the dcc protocol specification.
     */
    class DccCommandGenerator
    {
        public:
            DccCommandGenerator(DccInterface& _DccInterface):
                _DccInterface(_DccInterface)            
        {}

        private:
            DccInterface& _DccInterface;
            bool CalculateCheckSum(std::vector<char>& values);
    };
}

#endif