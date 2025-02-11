#ifndef __CENTRAL_ADDRESS_HPP__
#define __CENTRAL_ADDRESS_HPP__

#include<string>
#include<iostream>

namespace Central::Address
{
    struct IpV4IpPort
    {
        std::string ip = "127.0.0.1";
        int port;
    };

    std::ostream& operator<<(std::ostream& os, const Address::IpV4IpPort& ipV4IpPort);
}
#endif
