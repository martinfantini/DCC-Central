#ifndef __REST_API_SERIALIZER_TURNOUT__
#define __REST_API_SERIALIZER_TURNOUT__

#include <Common/Turnout.hpp>
#include <boost/json.hpp>

namespace RestApi::Serializer
{
    static boost::json::object ToJson(const Common::Turnout& loco);
    static Common::Turnout FromJson(const boost::json::object &obj);
}

#endif
