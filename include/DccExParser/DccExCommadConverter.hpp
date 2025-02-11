#ifndef __DCC_EX_COMMAND_CONVERTER_HPP__
#define __DCC_EX_COMMAND_CONVERTER_HPP__

#include "DccExBasicParser.hpp"
#include "CommandInterface.hpp"

#include <vector>
#include <functional>

namespace DccExParser
{
    typedef std::function<void(const std::string&)> string_function_type;

    class DccExCommandParser : public CallbackParser
    {
        public:
            DccExCommandParser(CommandInterface& _command_interface, string_function_type& send_response);
            virtual ~DccExCommandParser(){}

            void parsed_values(const char command, const std::vector<std::string>& parameters);

        private:
            CommandInterface& _command_interface;
            string_function_type& _send_response;
    };
}

#endif
