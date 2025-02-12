#ifndef __DCC_EX_COMMAND_CONVERTER_HPP__
#define __DCC_EX_COMMAND_CONVERTER_HPP__

#include "DccExBasicParser.hpp"
#include "CommandInterface.hpp"

#include <vector>
#include <functional>
#include <memory>

namespace DccExParser
{
    class DccExCommandResponse
    {
        public:
            virtual void send_response(const std::string& response) = 0;
    };

    class DccExCommandParser : public CallbackParser
    {
        public:
            DccExCommandParser(CommandInterface& _command_interface);

            virtual ~DccExCommandParser(){}

            void parsed_values(const char command, const std::vector<std::string>& parameters);

            void set_response_callback(std::shared_ptr<DccExCommandResponse> ptr_response)
            {
                response_ptr = ptr_response;
            }

        private:
            CommandInterface& _command_interface;
            std::shared_ptr<DccExCommandResponse> response_ptr;
    };
}

#endif
