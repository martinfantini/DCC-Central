#ifndef __CENTRAL_COMMAND_OPTIONS_HPP__
#define __CENTRAL_COMMAND_OPTIONS_HPP__

#include<utility>
#include<string>

namespace CommandOptions
{
    struct CommandParameters
    {
        std::string configFile = "";
    };

    /**
     * @brief This function is to parse the command line. It returns true if it is passed the correct parameters.
     */
    std::pair<bool, CommandParameters> ParseCommandOptions(int argc, char *argv[]);
}
#endif
