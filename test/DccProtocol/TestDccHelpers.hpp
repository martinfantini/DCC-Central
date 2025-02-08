#ifndef __DCC_PROTOCOL_TEST_CLASSES_HELPERS_HPP__
#define __DCC_PROTOCOL_TEST_CLASSES_HELPERS_HPP__

#include "DccInterface.hpp"

class TestMockDccInterface : public DccProtocol::DccInterface
{
    public:
        void SendToDCC(const std::vector<unsigned char>& buffer, int repeatCommand = 0, bool deliverAnswer = false)
        {
            _internal_buffer = buffer;
            _repeatCommand = repeatCommand;
            _deliverAnswer = deliverAnswer;
        }

        int ReceiveFromDCC()
        {
            return _result;
        }

        std::vector<unsigned char> _internal_buffer;
        int _repeatCommand;
        bool _deliverAnswer;        
        int _result;
};

#endif