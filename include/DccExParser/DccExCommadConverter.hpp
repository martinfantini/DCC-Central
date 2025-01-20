#ifndef __DCC_EX_COMMAND_CONVERTER_HPP__
#define __DCC_EX_COMMAND_CONVERTER_HPP__

#include "DccExBasicParser.hpp"
#include "CommandManager.hpp"

#include <vector>
#include <functional>

namespace DccExParser
{
    typedef std::function<void(const std::string&)> string_function;

    class DccExCommandParser : public CallbackParser
    {
        public:
            DccExCommandParser(Common::CommandManager& _command_manager, string_function& send_response, string_function& logger);
            virtual ~DccExCommandParser(){}

            void parsed_values(const char command, const std::vector<std::string>& parameters);

        private:

            bool parse_f(int params, const std::vector<std::string>& parameters);
            bool funcmap(int16_t cab, char value, int fstart, int fstop);

            Common::CommandManager& _manager;
            string_function& _send_response;
            string_function& _logger;
    };
}

#endif
