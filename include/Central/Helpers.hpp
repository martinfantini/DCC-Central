
#ifndef __CENTRAL_HELPERS_HPP__
#define __CENTRAL_HELPERS_HPP__

#include "Address.hpp"
#include <iostream>

namespace Central::Helpers
{   
    struct DCCPlus
    {
        bool enabled = false;
        Address::IpV4IpPort ipPort;
    };

    struct RestApi
    {
        bool enabled = false;
        Address::IpV4IpPort ipPort;
    };

    struct Logger
    {
        bool enabled = false;
        std::string format = "L | yyyymmdd hh:mm:ss.uuuuuu | threadid | file:line | msg";
        int level;
        std::string logPath;
    };

    struct Track
    {
        bool isMain = false;
        int PowerPin = 0;
        int SignalPin = 0;
        int EnablePin = 0;
        float SenseFactor = 0.0;
        unsigned int TripMilliamps = 0;
    };

    std::ostream& operator<<(std::ostream& os, const Helpers::DCCPlus& _dccPlus);
    std::ostream& operator<<(std::ostream& os, const Helpers::RestApi& _restApi);
    std::ostream& operator<<(std::ostream& os, const Helpers::Logger& _logger);
} // namespace Helpers

#endif
