#include "DccExBasicParser.hpp"

namespace DccExParser
{
    DCCBasicParser::DCCBasicParser(CallbackParser& parse_result):
        _parse_result(parse_result)
    {}

    void DCCBasicParser::read_stream(const std::string& input_stream)
    {
        static enum parsingState {
            FIND_START = 0,
            PARSE_COMMAND,
            PARSING_COMPLETE,
        } parsing_state = FIND_START;

        std::string parameter;
        std::vector<std::string> parameters_data;

        for(std::string::size_type i = 0; i < input_stream.size(); ++i) 
        {
            if (parsing_state == FIND_START)
            {
                if (input_stream[i] == '<')
                {
                    parameter.clear();
                    parameters_data.clear();
                    parsing_state = PARSE_COMMAND;
                }
                continue;
            }
            
            if (parsing_state == PARSE_COMMAND)
            {
                if (input_stream[i] == ' ')
                {
                    parameters_data.push_back(parameter);
                    parameter.clear();
                }
                else if (input_stream[i] == '>')
                {
                    parameters_data.push_back(parameter);
                    parameter.clear();                    
                    parsing_state = PARSING_COMPLETE;
                }
                else
                {
                   parameter.push_back(input_stream[i]);
                }
            }

            if (parsing_state == PARSING_COMPLETE)
            {
                _parse_result.parsed_values(parameters_data);
                parameters_data.clear();
                parsing_state = FIND_START;
            }
        }
    }
}
