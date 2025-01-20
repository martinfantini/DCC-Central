#include <catch2/catch_test_macros.hpp>

#define TEST_XML_HELPERS

#include "XmlHelpers.hpp"

TEST_CASE("Test XMLReader class")
{
    using namespace XmlHelpers;

    SECTION("Test DCC configuration")
    {
        std::string ip_value("127.0.0.1");
        int port = 1258;

        pugi::xml_document doc;
        pugi::xml_node node_dcc = doc.append_child("DCCPlus");
        {
            node_dcc.append_child("IP").text().set(ip_value.c_str());
            node_dcc.append_child("Port").text().set(std::to_string(port).c_str());
        }
       
        XMLReader xml("any");
        auto result = xml.ReadDccPlus(node_dcc);

        CHECK(result.first);
        CHECK(result.second.enabled);
        CHECK(result.second.ipPort.ip == ip_value);
        CHECK(result.second.ipPort.port == port);
    }

    SECTION("Test ApiRest configuration")
    {
        std::string ip_value("127.0.0.1");
        int port = 1258;

        pugi::xml_document doc;
        pugi::xml_node node_rest_api = doc.append_child("ApiRest");
        {
            node_rest_api.append_child("IP").text().set(ip_value.c_str());
            node_rest_api.append_child("Port").text().set(std::to_string(port).c_str());
        }
       
        XMLReader xml("any");
        auto result = xml.ReadRestApi(node_rest_api);

        CHECK(result.first);
        CHECK(result.second.enabled);
        CHECK(result.second.ipPort.ip == ip_value);
        CHECK(result.second.ipPort.port == port);
    }

    SECTION("Test Interfaces")
    {
        std::string ip_value_dcc("127.0.0.1");
        int port_dcc = 1258;

        std::string ip_value_rest("0.0.0.0");
        int port_rest = 1258;

        pugi::xml_document doc;
        pugi::xml_node node_interfaces = doc.append_child("Interfaces");

        {
            pugi::xml_node node_dcc = node_interfaces.append_child("DCCPlus");
            node_dcc.append_child("IP").text().set(ip_value_dcc.c_str());
            node_dcc.append_child("Port").text().set(std::to_string(port_dcc).c_str());
        }        
        
        {
            pugi::xml_node node_rest_api = node_interfaces.append_child("ApiRest");
            node_rest_api.append_child("IP").text().set(ip_value_rest.c_str());
            node_rest_api.append_child("Port").text().set(std::to_string(port_rest).c_str());
        }

        XMLReader xml("any");
        CHECK(xml.ReadInterfaces(node_interfaces));
        CHECK(xml.GetConfiguration().getDCC().enabled);
        CHECK(xml.GetConfiguration().getDCC().ipPort.ip == ip_value_dcc);
        CHECK(xml.GetConfiguration().getDCC().ipPort.port == port_dcc);

        CHECK(xml.GetConfiguration().getRestApi().enabled);
        CHECK(xml.GetConfiguration().getRestApi().ipPort.ip == ip_value_rest);
        CHECK(xml.GetConfiguration().getRestApi().ipPort.port == port_rest);
    }

    SECTION("Test Read Logger")
    {
        std::string strPath = "/home/rmfantini/Projects/Ralf_Platine/DCC-Central/log/";

        pugi::xml_document doc;
        pugi::xml_node node_logger = doc.append_child("Logger");
        {
            node_logger.append_child("Level").text().set("warning");
            node_logger.append_child("Folder").text().set(strPath.c_str());
        }

        XMLReader xml("any");
        CHECK(xml.ReadLogger(node_logger));
        CHECK(xml.GetConfiguration().getLogger().enabled);
        CHECK(xml.GetConfiguration().getLogger().level == 1);
        CHECK(xml.GetConfiguration().getLogger().logPath == strPath);
    }
}
