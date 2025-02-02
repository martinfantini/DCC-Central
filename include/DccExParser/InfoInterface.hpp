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
                static const std::string strVersion = \
                    std::string("DCC Protocol: Version: '")
                    + std::to_string(LIB_DCC_EX_VERSION_HI) + "."
                    + std::to_string(LIB_DCC_EX_VERSION_LO) + "'";;
                return strVersion;
            }

            virtual const std::string& getAdditionVersionInfo() = 0;
            virtual ~InfoInterface(){}
    };
}
#endif