#include <Helpers/CommandOptions.hpp>
#include <Helpers/Logger.hpp>
#include <Configuration/XmlHelpers.hpp>
#include <Configuration/Configuration.hpp>

#include <glog/logging.h>

#include <iostream>

using namespace Central;

int main(int argc, char *argv[]) 
{
    auto parseCommand = CommandOptions::ParseCommandOptions(argc, argv);
    if(!parseCommand.first)
    {
        std::cout << "Error on passing command parameters" << std::endl;
        return 1;
    }
       
    if (parseCommand.second.configFile.empty())
    {
        std::cout << "The config file paramater is empty" << std::endl;
        return 1;
    }

    auto xmlReader = XmlHelpers::XMLReader(parseCommand.second.configFile);

    if (!xmlReader.Parse())
    {
        std::cout << "The error while parse xml" << std::endl;
        return 1;
    }

    Configuration::Config _config = xmlReader.GetConfiguration();
    
    // Initialize Logger for the Module
    Logger::InitializeLogger(_config.getLogger());

    // Log the configuration
    LOG(INFO) << "Actual configuration is: \n";
    LOG(INFO) <<  _config;

    // Start the thread to receive messages from DCC protocol





    return 0;
}
