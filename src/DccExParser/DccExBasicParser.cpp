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
            PARSE_PARAMETERS,
            PARSING_COMPLETE,
        } parsing_state = FIND_START;

        std::string current_parsing;
        std::vector<std::string> parameters;
        char command;

        for(std::string::size_type i = 0; i < input_stream.size(); ++i) 
        {
            if (parsing_state == FIND_START)
            {
                if (input_stream[i] == '<')
                {
                    current_parsing.clear();
                    parameters.clear();
                    command = ' ';
                    parsing_state = PARSE_COMMAND;
                }
                continue;
            }

            if (parsing_state == PARSE_COMMAND)
            {
                command = input_stream[i];
                current_parsing.clear();
                parsing_state = PARSE_PARAMETERS;
                continue;
            }

            if (parsing_state == PARSE_PARAMETERS)
            {
                if (input_stream[i] == ' ')
                {
                    if (!current_parsing.empty())
                        parameters.push_back(current_parsing);
                    current_parsing.clear();
                }
                else if (input_stream[i] == '>')
                {
                    if (!current_parsing.empty())
                        parameters.push_back(current_parsing);
                    current_parsing.clear();
                    parsing_state = PARSING_COMPLETE;
                }
                else
                {
                   current_parsing.push_back(input_stream[i]);
                }
            }

            if (parsing_state == PARSING_COMPLETE)
            {
                _parse_result.parsed_values(command, parameters);
                current_parsing.clear();
                parameters.clear();
                command = ' ';
                parsing_state = FIND_START;
            }
        }
    }
}
