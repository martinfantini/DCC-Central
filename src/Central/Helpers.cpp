#include "Helpers.hpp"
#include<ios>

namespace Helpers
{
    using namespace Address;

    std::ostream& operator<<(std::ostream& os, const DCCPlus& _dccPlus)
    {
        os << "DCC Configuration Configuration:\n";
        os << "    Enabled: " << std::boolalpha << _dccPlus.enabled << "\n";
        os << "    Address Info:" << _dccPlus.ipPort;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const RestApi& _restApi)
    {
        os << "ApiRest Configuration:\n";
        os << "    Enabled: " << std::boolalpha << _restApi.enabled << "\n";
        os << "    Address Info:" << _restApi.ipPort << "\n";
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Logger& _logger)
    {
        os << "Logger Configuration:\n";
        os << "    Enabled: " << std::boolalpha << _logger.enabled << "\n";
        os << "    Level: " << std::to_string(_logger.level) << "\n";
        os << "    Path:" << _logger.logPath << "\n";
        return os;
    }

}
