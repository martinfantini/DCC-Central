#ifndef __REST_API_SERIALIZER_ACCESSORY__
#define __REST_API_SERIALIZER_ACCESSORY__

#include <Common/Accessory.hpp>
#include <boost/json.hpp>

namespace RestApi::Serializer
{
    static boost::json::object ToJson(const Common::Accessory &accessory);
    static Common::Accessory FromJson(const boost::json::object &obj);
}

#endif
