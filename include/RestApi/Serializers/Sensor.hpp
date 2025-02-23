#ifndef __REST_API_SERIALIZER_SENSOR__
#define __REST_API_SERIALIZER_SENSOR__

#include <Common/Sensor.hpp>
#include <boost/json.hpp>

namespace RestApi::Serializer
{
    boost::json::object ToJson(const Common::Sensor& loco);
    Common::Sensor FromJson(const boost::json::object &obj);
}

#endif
