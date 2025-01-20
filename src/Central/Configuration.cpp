#include "Configuration.hpp"

#include <iostream>
namespace Configuration
{
    using namespace Helpers;

    std::ostream& operator<<(std::ostream& os, const Configuration::Config& config)
    {
        os << "\n";
        os << config._dccPlus;
        os << "\n";
        os << config._restApi;
        os << config._logger;
        os << "\n";
        return os;
    }
}

   
