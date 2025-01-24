#ifndef __DCC_EX_INFO_INTERFACE_HPP__
#define __DCC_EX_INFO_INTERFACE_HPP__

#include <string>
#include <unordered_map>

namespace DccExParser
{
    class InfoInterface
    {
        public:
            const std::string& getDCCVersion()
            {
                static const std::string strVersion = std::string("DCC Protocol: Version: '") 
                    + \
                    std::to_string(DCC_PROTOCOL_VERSION_1) + \
                    "." + \
                    std::to_string(DCC_PROTOCOL_VERSION_2) + \
                    "." + \
                    std::to_string(DCC_PROTOCOL_VERSION_3) + \
                    "." + \
                    std::to_string(DCC_PROTOCOL_VERSION_4) + \
                    "'";
                return strVersion;
            }

            virtual const std::string& getAdditionVersionInfo() = 0;
            virtual ~InfoInterface(){}
    };
}
#endif