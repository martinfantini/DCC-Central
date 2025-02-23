#ifndef __REST_API_SERIALIZER_TURNOUT__
#define __REST_API_SERIALIZER_TURNOUT__

#include <Common/Turnout.hpp>
#include <boost/json.hpp>

namespace RestApi::Serializer
{
    boost::json::object ToJson(const Common::Turnout& loco);
    Common::Turnout FromJson(const boost::json::object &obj);
}

#endif
