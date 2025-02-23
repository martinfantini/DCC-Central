#include <Manager/InfoManager.hpp>

namespace Central
{
    const std::string& InfoManager::getAdditionVersionInfo()
    {
        static const std::string strVersion = \
            std::string("Central: Version: '")
            + std::to_string(EXECUTABLE_CENTRAL_VERSION_HI) + "."
            + std::to_string(EXECUTABLE_CENTRAL_VERSION_LO) + "'";;
        return strVersion;
    }
}
