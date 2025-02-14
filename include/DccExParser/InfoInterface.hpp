#ifndef __DCC_EX_INFO_INTERFACE_HPP__
#define __DCC_EX_INFO_INTERFACE_HPP__

#include <string>
#include <unordered_map>

namespace DccExParser
{
    class InfoInterface
    {
        public:
            const std::string& getDCCVersion();

            virtual const std::string& getAdditionVersionInfo() = 0;
            virtual ~InfoInterface(){}
    };
}
#endif