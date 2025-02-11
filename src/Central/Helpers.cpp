#include "Helpers.hpp"
#include<ios>

namespace Central::Helpers
{
    using namespace Central::Address;

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

    std::ostream& operator<<(std::ostream& os, const Track& _track)
    {
        os << "Track Configuration:\n";
        os << "    Type: " << std::string(_track.isMain ? "Main" :"Progaming") << "\n";
        os << "    Power Pin: " << std::to_string(_track.PowerPin) << "\n";
        os << "    Signal Pin: " << std::to_string(_track.SignalPin) << "\n";
        os << "    Enable Pin: " << std::to_string(_track.EnablePin) << "\n";
        os << "    Sense Factor: " << std::to_string(_track.SenseFactor) << "\n";
        os << "    Trip Miliamps: " << std::to_string(_track.TripMilliamps) << "\n";
        return os;
    }
}
