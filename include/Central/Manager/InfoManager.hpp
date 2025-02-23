#ifndef __CENTRAL_INFO_MANAGER_HPP__
#define __CENTRAL_INFO_MANAGER_HPP__

#include <string>
#include <DccExParser/InfoInterface.hpp>

namespace Central
{
    class InfoManager : public DccExParser::InfoInterface
    {
        public:
            virtual const std::string& getAdditionVersionInfo() override;
    };
}

#endif
