#include "Helpers/CommandOptions.hpp"

#include <boost/program_options.hpp>

#include <filesystem>
#include <iostream>
#include <string>

namespace Central::CommandOptions
{
    namespace po = boost::program_options;

    std::pair<bool, CommandParameters> ParseCommandOptions(int argc, char *argv[])
    {
        // Define the options
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help,h", "produce help message")
            ("version,v", "Version 0.1")
            ("config,c", po::value<std::string>(), "configuration file, it has to be an xml configuration file");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return {false, {}};
        }

        if (vm.count("version")) {
            std::cout << "Version 0.1" << std::endl;
            return {false, {}};
        }

        // Check if the required options are provided
        if (!vm.count("config")) {
            std::cerr << "Error: Configuration file must be specified." << std::endl;
            std::cout << desc << std::endl;
            return {false, {}};
        }

        // Retrieve the values of the options
        std::string configFile = vm["config"].as<std::string>();

        if (!std::filesystem::exists(configFile))
        {
            std::cout << "The config file does not exist '" << configFile << "'" <<  std::endl;
            return {false, {}};
        }

        // Print the options and their values
        std::cout << "Config file: '" << configFile << "'" <<  std::endl;

        return {true, { .configFile = configFile}};
    }
}