#include "Address.hpp"

namespace Address
{
    std::ostream& operator<<(std::ostream& os, const Address::IpV4IpPort& ipV4IpPort)
    {
        os << "[Address Info: Ip: '" << ipV4IpPort.ip << "', Port: '" << ipV4IpPort.port << "' ]";
        return os;
    }
}