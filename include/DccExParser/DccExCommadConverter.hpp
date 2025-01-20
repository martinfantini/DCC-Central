#ifndef __DCC_EX_COMMAND_CONVERTER_HPP__
#define __DCC_EX_COMMAND_CONVERTER_HPP__

#include "DccExBasicParser.hpp"
#include "Common/CommandManager.hpp"

#include <vector>
#include <functional>

namespace DccExParser
{
    typedef std::function<void(const std::string&)> response_function;

    class DccExCommandParser : public CallbackParser
    {
        public:
            DccExCommandParser(Common::CommandManager& _command_manager, response_function& send_response);
            virtual ~DccExCommandParser(){}

            void parsed_values(const std::vector<std::string>& parsed_values);
        private:
            Common::CommandManager& _manager;
            response_function& _send_response;
    };
}

#endif
