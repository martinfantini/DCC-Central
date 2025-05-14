
#ifndef __CENTRAL_XML_TAGS_HPP__
#define __CENTRAL_XML_TAGS_HPP__

namespace Central::XmlTags
{
    namespace IpV4
    {
        inline static const char* Ip = "IP";
        inline static const char* Port = "Port";
    }

    namespace Interface
    {
        inline static const char* Interfaces = "Interfaces";
        inline static const char* DccPlus = "DCCPlus";
        inline static const char* ApiRest = "ApiRest";
    }

    namespace Logger
    {
        inline static const char* Logger = "Logger";
        inline static const char* Level = "Level";
        inline static const char* Format = "Format";
        inline static const char* Folder = "Folder";
    }

    namespace Track
    {
        inline static const char* Track             = "Track";
        inline static const char* Main              = "Main";
        inline static const char* Programming       = "Programming";
        inline static const char* PowerPin          = "PowerPin";
        inline static const char* SignalPin         = "SignalPin";
        inline static const char* EnablePin         = "EnablePin";
        inline static const char* SenseFactor       = "SenseFactor";
        inline static const char* TripMilliAmperes  = "TripMilliAmperes";
        inline static const char* MaxCurrentInMilli = "MaxCurrentInMilli";
    }
}
#endif
