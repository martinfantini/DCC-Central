#ifndef __DCC_EX_COMMAND_CONVERTER_HPP__
#define __DCC_EX_COMMAND_CONVERTER_HPP__

#include "DccExParser.hpp"
#include "Common/CommandManager.hpp"
#include <vector>

namespace DccExParser
{
    class DccExCommandConverter : public CallbackParser
    {
    public:
        DccExCommandConverter(Common::CommandManager& manager);

        virtual ~DccExCommandConverter()
        {}
        
        private:
            void parsed_values(const std::vector<std::string>& parsed_values);

        Common::CommandManager& _manager;
    };
}

#endif
