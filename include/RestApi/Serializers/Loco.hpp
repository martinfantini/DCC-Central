#ifndef __REST_API_SERIALIZER_LOCO__
#define __REST_API_SERIALIZER_LOCO__

#include <Common/Loco.hpp>
#include <boost/json.hpp>

namespace RestApi::Serializer
{
    boost::json::object ToJson(const Common::Loco& loco);
    Common::Loco FromJson(const boost::json::object &obj);
}

#endif
