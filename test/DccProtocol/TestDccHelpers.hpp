#ifndef __DCC_PROTOCOL_TEST_CLASSES_HELPERS_HPP__
#define __DCC_PROTOCOL_TEST_CLASSES_HELPERS_HPP__

#include "DccInterface.hpp"

class TestMockDccInterface : public DccProtocol::DccInterface
{
    public:
        void SendToDCC(const std::vector<unsigned char>& buffer, int repeatCommand = 0)
        {
            _internal_buffer = buffer;
            _repeat = repeatCommand;
        }

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
        int _repeat = 0;
        bool _isWriteCommand;
        unsigned char _result;
};
#endif
