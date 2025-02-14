#ifndef __REST_API_SERIALIZER_LOCO__
#define __REST_API_SERIALIZER_LOCO__

#include <Common/Loco.hpp>
#include <boost/json.hpp>

namespace RestApi::Serializer
{
    static boost::json::object ToJson(const Common::Loco& loco);
    static Common::Loco FromJson(const boost::json::object &obj);
}

#endif
