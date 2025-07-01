#include <Configuration/XmlHelpers.hpp>

#include <iostream>
#include <regex>
#include <filesystem>
#include <cstring>

#include <Configuration/XmlTags.hpp>

namespace Central::XmlHelpers
{
    XMLReader::XMLReader(const std::string& path_to_xml):
        _path_to_xml(path_to_xml)
    {}

    bool XMLReader::Parse()
    {    
        pugi::xml_parse_result result = _doc.load_file(_path_to_xml.c_str());
        if (!result)
        {
            std::cout << "The file name " << _path_to_xml << " does not exists.\n";
            return false;
        }
        ReadInterfaces(_doc.child(XmlTags::Interface::Interfaces));
        ReadLogger(_doc.child(XmlTags::Logger::Logger));
        return true;
    }

    std::pair<bool, Address::IpV4IpPort> XMLReader::ReadIpV4IpPort(const pugi::xml_node& node)
    {
        std::string ip = node.child_value(XmlTags::IpV4::Ip);
        if (ip.empty())
        {
            ip = "127.0.0.1";
            std::cout << "Not configured the Ip, using localhost (" << ip << ").\n";
        }

        std::string port = node.child_value(XmlTags::IpV4::Port);
        if (port.empty())
        {
            std::cout << "Not configured the port.\n";
            return {false, {}};
        }

        // Regex expression for validating IPv4
        std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
        if (!std::regex_match(ip, ipv4))
        {
            std::cout << "Not valid IP Address.\n";
            return {false, {}};
        }
        return {true, {.ip = ip, .port = atoi(port.c_str())} };
    }
        
    bool XMLReader::ReadLogger(const pugi::xml_node& node)
    {
        if(strcmp(XmlTags::Logger::Logger, node.name()) != 0)
            return false;

        Helpers::Logger _logger;
        {
            int level = 0;
            std::string _level = node.child_value(XmlTags::Logger::Level);
            if (!_level.empty())
            {  
                std::transform(_level.begin(), _level.end(), _level.begin(),
                        [](unsigned char c){ return std::tolower(c); });
                if (_level == "warning")
                    level = 1;
                else if (_level == "error")
                    level = 2;
                else if (_level == "fatal")
                    level = 3;
            }
            _logger.level = level;
        }
        {
            std::string logPath = node.child_value(XmlTags::Logger::Folder);
            if (logPath.empty())
            {
                std::cout << "Logger does not have set the path.\n";
                return false;
            }

            {
                std::filesystem::directory_entry entry{logPath};
                if (!entry.exists())
                {
                    std::cout << "Logger path does not exists '" << logPath << "'.\n";
                    return false;
                }
            }
            _logger.logPath = logPath;
        }
        
        _logger.enabled = true;
        _config.setLogger(_logger);
        return true;
    }

    bool XMLReader::ReadInterfaces(const pugi::xml_node& node)
    {
        if(strcmp(XmlTags::Interface::Interfaces, node.name()) != 0)
            return false;

        // check for the dcc configuration
        {
            pugi::xml_node child = node.child(XmlTags::Interface::DccPlus);
            if (child)
            {
                auto result = ReadDccPlus(child);
                if(result.first)
                    _config.setDCC(result.second);
            }
        }

        // check for the api rest configuration
        {
            pugi::xml_node child = node.child(XmlTags::Interface::ApiRest);
            if (child)
            {
                auto result = ReadRestApi(child);
                if(result.first)
                    _config.setRestApi(result.second);
            }
        }

        return true;
    }    

    std::pair<bool, Helpers::RestApi> XMLReader::ReadRestApi(const pugi::xml_node& node)
    {
        Helpers::RestApi _restApi;
        auto ipPort = ReadIpV4IpPort(node);
        if (!ipPort.first)
            return {false, _restApi};
        
        _restApi.enabled = true;
        _restApi.ipPort = ipPort.second;
        return {true, _restApi};
    }

    std::pair<bool, Helpers::DCCPlus> XMLReader::ReadDccPlus(const pugi::xml_node& node)
    {
        Helpers::DCCPlus _dccPlus;
        auto ipPort = ReadIpV4IpPort(node);
        if (!ipPort.first)
            return {false, _dccPlus};
        
        _dccPlus.enabled = true;
        _dccPlus.ipPort = ipPort.second;
        return {true, _dccPlus};
    }

    std::pair<bool, Helpers::Track> XMLReader::ReadOneTrack(const pugi::xml_node& node)
    {
        Helpers::Track _track;

        {
            std::string _pin = node.child_value(XmlTags::Track::PowerPin);
            if (!_pin.empty())
            {
                _track.PowerPin = atoi(_pin.c_str());
            }
        }

        {
            std::string _pin = node.child_value(XmlTags::Track::SignalPin);
            if (!_pin.empty())
            {
                _track.SignalPin = atoi(_pin.c_str());
            }
        }

        {
            std::string _pin = node.child_value(XmlTags::Track::EnablePin);
            if (!_pin.empty())
            {
                _track.EnablePin = atoi(_pin.c_str());
            }
        }

        {
            std::string _pin = node.child_value(XmlTags::Track::SenseFactor);
            if (!_pin.empty())
            {
                _track.SenseFactor = std::stof(_pin.c_str());
            }
        }

        {
            std::string _pin = node.child_value(XmlTags::Track::TripMilliAmperes);
            if (!_pin.empty())
            {
                _track.SenseFactor = atoi(_pin.c_str());
            }
        }

        return {true, _track};
    }

    bool XMLReader::ReadTrack(const pugi::xml_node& node)
    {
        if(strcmp(XmlTags::Track::Track, node.name()) != 0)
            return false;

        // check the main configuration
        {
            pugi::xml_node child = node.child(XmlTags::Track::Main);
            if (child)
            {
                auto result = ReadOneTrack(child);
                if(result.first)
                {
                    result.second.isMain = true;
                    _config.setMainTrack(result.second);
                }
            }
            else
            {
                return false;
            }
        }

        {
            pugi::xml_node child = node.child(XmlTags::Track::Programming);
            if (child)
            {
                auto result = ReadOneTrack(child);
                if(result.first)
                {
                    _config.setProgramingTrack(result.second);
                }
            }
        }
        return true;
    }
}
