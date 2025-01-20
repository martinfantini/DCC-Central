
#ifndef __DCC_EX_PARSER_HPP__
#define __DCC_EX_PARSER_HPP__

#include <iostream>
#include <vector>
#include <string>

namespace DccExParser
{
    class CallbackParser
    {
        private:
            virtual void parsed_values(const std::vector<std::string>& parsed_values) = 0;
    };

    class Parser
    {
        public:
            Parser(CallbackParser& parse_result);
            void read_stream(const std::string& input_stream);

        private:
            CallbackParser& _parse_result;
    };
}
#endif
