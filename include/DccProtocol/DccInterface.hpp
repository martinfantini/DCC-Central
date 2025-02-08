#ifndef __DCC_PROTOCOL_DCC_INTERFACE_HPP__
#define __DCC_PROTOCOL_DCC_INTERFACE_HPP__

#include<vector>

namespace DccProtocol
{
    /**
     * @brief Classs to send the commands to the DCC interface
     * This class generate the commands to be send to the electrical part of the protocol.
     */
    class DccInterface
    {
        public:
            /**
             * @brief Electrical part to send in the protocol
             * 
             * @param buffer to be send to the wire.
             */
            virtual void SendToDCC(const std::vector<unsigned char>& buffer, int RepeatCommand = 0) = 0;
            /**
             * @brief to send a CV with the corresponding ACK answer from the wire.
             *      With this command the instruction will be repeat.
             *
             * @param buffer Send the buffer to read.
             * @return unsigned char with the read bit. It can return a 1 or 0,
             *      depending on the read bit.
             */
            virtual unsigned char SendToDCCWithAck(const std::vector<unsigned char>& buffer, bool isWriteCommand) = 0;
    };
}

#endif
