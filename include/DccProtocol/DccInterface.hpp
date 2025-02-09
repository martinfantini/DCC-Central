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
             * @brief Electrical part to send in the protocol.
             *  IMPORTANT: All this commands are done in the main track.
             * 
             * @param buffer to be send to the wire.
             */
            virtual void SendToDCC(const std::vector<unsigned char>& buffer, int RepeatCommand = 0) = 0;
    };
}

#endif
