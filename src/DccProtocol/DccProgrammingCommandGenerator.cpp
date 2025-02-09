#include "DccProgrammingCommandGenerator.hpp"
#include "DccConstants.hpp"

namespace DccProtocol
{
    using namespace DccProtocol::DccConstants;

    std::pair<bool, unsigned char> DccProgrammingCommandGenerator::ReadCV(unsigned int CV)
    {
        unsigned char cv_Value = 0x00;
        // decrement minus 1 because the CV 1 is the 0x00 
        CV--;
        
        std::vector<unsigned char> buffer;     

        for (int idx = 0; idx < 8; idx++)
        {
            buffer.clear();
            buffer.emplace_back(0x78 | (CV >> 8));
            buffer.emplace_back(CV & 0xFF);
            buffer.emplace_back(0xE8 | idx);
            if (m_DccProgrammingInterface.SendToDCCWithAck(buffer, false))
            {
                cv_Value |= (1 << idx);
            }
        }
    
        // check complete byte:
        buffer.clear();
        buffer.emplace_back(0x74 | (CV >> 8));
        buffer.emplace_back(CV & 0xFF);
        buffer.emplace_back(cv_Value);
        if (m_DccProgrammingInterface.SendToDCCWithAck(buffer, false))
        {
            return {true, cv_Value};
        }
        return {false, 0x00};
    }

    std::pair<bool, unsigned char> DccProgrammingCommandGenerator::WriteCV(unsigned int CV, unsigned char Value)
    {
        if (CV < 1)
            return {false, 0x00};

        // decrement minus 1 because the CV 1 is the 0x00 
        CV--;
        
        std::vector<unsigned char> buffer;
        buffer.emplace_back(0x7C | (CV >> 8));
        buffer.emplace_back(CV & 0xFF);
        buffer.emplace_back(Value);

        if (m_DccProgrammingInterface.SendToDCCWithAck(buffer, true) == 1)
        {
            buffer.clear();
            // check complete byte:
            buffer.emplace_back(0x74 | (CV >> 8));
            buffer.emplace_back(CV & 0xFF);
            buffer.emplace_back(Value);

            if (m_DccProgrammingInterface.SendToDCCWithAck(buffer, false) == 1)
            {
                return {true, Value};
            }
            else
            {
                return {false, 0x00};
            }
        }
        else
        {
            return {false, 0x00};
        }
    }

    std::pair<bool, unsigned char> DccProgrammingCommandGenerator::WriteCVBit(unsigned int CV, unsigned int BitPosition, unsigned char Value)
    {
        if (BitPosition < 1 || BitPosition > 8)       
            return {false, 0x00};

        if (CV < 1)
            return {false, 0x00};

        // decrement minus 1 because the CV 1 is the 0x00 
        CV--;

        std::vector<unsigned char> buffer;
        buffer.emplace_back(0x78 | (CV >> 8));
        buffer.emplace_back(CV & 0xFF);
        buffer.emplace_back(0xF0 | (Value << 3) | BitPosition);

        if (m_DccProgrammingInterface.SendToDCCWithAck(buffer, 1) == 1)
        {
            buffer.clear();
            // check bit:
            buffer.emplace_back(0x78 | (CV >> 8));
            buffer.emplace_back(CV & 0xFF);
            buffer.emplace_back(0xE0 | (Value << 3) | BitPosition);
            if (m_DccProgrammingInterface.SendToDCCWithAck(buffer, 0) == 1)
            {
                return {true, Value};
            }
            else
            {
                return {false, 0x00};
            }
        }
        else
        {
            return {false, 0x00};
        }
    }

    std::pair<bool, unsigned char> DccProgrammingCommandGenerator::ReadCVBit(unsigned int CV, unsigned int BitPosition)
    {
        if (BitPosition < 1 || BitPosition > 8)
            return {false, 0x00};

        auto result = ReadCV(CV);
        if (!result.first)
            return {false, 0x00};

        if ((result.second & (1 << (BitPosition - 1))) != 0)
            return {true, 1};

        return {true, 0};
    }

    bool DccProgrammingCommandGenerator::WriteAddress(unsigned int Address)
    {
        if (Address > HIGHEST_SHORT_ADDR)
        {
            unsigned char addr_high = (Address >> 8) | 0xC0;
            unsigned char addr_low  = Address & 0xFF;

            auto write_high = WriteCV(17, addr_high);
            auto write_low  = WriteCV(18, addr_low);
            auto write_long_address = WriteCVBit(29, 5, 1);

            if (write_high.first && write_low.first && write_long_address.first)
            {
                return true;
            }
        }
        else
        {
            auto write_address = WriteCV(17, Address);
            auto write_short_address = WriteCVBit(29, 5, 1);

            if (write_address.first && write_short_address.first)
            {
                return true;
            }
        }
        return false;
    }
}
