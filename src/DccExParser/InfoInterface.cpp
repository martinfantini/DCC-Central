#include "InfoInterface.hpp"

namespace DccExParser
{
    const std::string& InfoInterface::getDCCVersion()
    {
        static const std::string strVersion = \
            std::string("DCC Protocol: Version: '")
            + std::to_string(LIB_DCC_EX_VERSION_HI) + "."
            + std::to_string(LIB_DCC_EX_VERSION_LO) + "'";;
        return strVersion;
    }
}
