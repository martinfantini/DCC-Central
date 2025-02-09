#ifndef __DCC_PROTOCOL_DCC_PROGRAMMING_INTERFACE_HPP__
#define __DCC_PROTOCOL_DCC_PROGRAMMING_INTERFACE_HPP__

#include<vector>

namespace DccProtocol
{
    /**
     * @brief Classs to send the commands to the DCC interface
     * This class generate the commands to be send to the electrical part of the protocol.
     */
    class DccProgrammingInterface
    {
        public:
            /**
             * @brief to send a CV with the corresponding ACK answer from the wire.
             *      With this command the instruction will be repeat.
             *  IMPORTANT: All this commands are done in Programming Track.
             *
             * @param buffer Send the buffer to read.
             * @return unsigned char with the read bit. It can return a 1 or 0,
             *      depending on the read bit.
             */
            virtual unsigned char SendToDCCWithAck(const std::vector<unsigned char>& buffer, bool isWriteCommand) = 0;

            virtual ~DccProgrammingInterface(){}
    };
}

#endif
