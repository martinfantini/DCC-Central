#ifndef __CENTRAL_XML_HELPERS_HPP__
#define __CENTRAL_XML_HELPERS_HPP__

#include <string>
#include <utility> 

#include "Address.hpp"
#include "Helpers.hpp"
#include "Configuration.hpp"

#include "pugixml.hpp"

namespace XmlHelpers
{
    class XMLReader
    {
    public:
        XMLReader(const std::string& path_to_xml);

        bool Parse();

        const ::Configuration::Config& GetConfiguration()
        {
            return _config;
        };

#ifndef TEST_XML_HELPERS
    private:
#endif
        std::pair<bool, Address::IpV4IpPort> ReadIpV4IpPort(const pugi::xml_node& node);
        
        bool ReadInterfaces(const pugi::xml_node& node);
        std::pair<bool, Helpers::RestApi> ReadRestApi(const pugi::xml_node& node);
        std::pair<bool, Helpers::DCCPlus> ReadDccPlus(const pugi::xml_node& node);
        bool ReadTrack(const pugi::xml_node& node);
        std::pair<bool, Helpers::Track> ReadOneTrack(const pugi::xml_node& node);

        bool ReadLogger(const pugi::xml_node& node);

    private:
        ::Configuration::Config _config;
        std::string _path_to_xml;
        pugi::xml_document _doc;
    };
}
#endif
