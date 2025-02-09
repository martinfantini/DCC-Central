#ifndef __DCC_PROTOCOL_TEST_PROGRAMMING_CLASSES_HELPERS_HPP__
#define __DCC_PROTOCOL_TEST_PROGRAMMING_CLASSES_HELPERS_HPP__

#include "DccProgrammingInterface.hpp"

class TestMockDccProgrammingInterface : public DccProtocol::DccProgrammingInterface
{
    public:
        unsigned char SendToDCCWithAck(const std::vector<unsigned char>& buffer, bool isWriteCommand)
        {
            _internal_buffer = buffer;
            _isWriteCommand = isWriteCommand;
            return _result;
        }

        void SetResult(unsigned char commandResult)
        {
            _result = commandResult;
        }

        std::vector<unsigned char> _internal_buffer;
        bool _isWriteCommand;
        unsigned char _result;
};
#endif
