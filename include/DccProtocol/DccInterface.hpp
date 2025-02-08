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
             * @param buffer to be send n the wire
             */
            virtual void SendToDCC(const std::vector<unsigned char>& buffer, int RepeatCommand = 0, bool DeliverAnAnswer = false) = 0;
            /**
             * @brief to receive ddata from the DCC protocol. This method is to be called, if the current command 
             * has set the deliverAnswer in true.
             * 
             * @return int value with the command. Because the int are 4 bytes, is it the best to deliver an output
             */
            virtual int ReceiveFromDCC() = 0;
    };
}

#endif
