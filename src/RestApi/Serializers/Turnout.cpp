#include <Serializers/Turnout.hpp>

#include <map>
#include <string>

namespace RestApi::Serializer
{
    using namespace Common;

    boost::json::object TurnoutSerializer::ToJson(const Common::Turnout& turnout)
    {
        boost::json::object obj;
        obj["Id"] = turnout.Id;
        obj["Address"] = turnout.Address;
        obj["SubAddress"] = turnout.SubAddress;
        obj["Pin"] = turnout.Pin;

        {
            std::map<StatusTurnout, std::string> helper_map
            {
                {StatusTurnout::StatusTurnout_None  ,"None"},
                {StatusTurnout::Close ,"Close"},
                {StatusTurnout::Throw ,"Throw"},
            };

            auto found = helper_map.find(turnout.Status);
            if (found != helper_map.end())
            {
                obj["Status"] = (*found).second;
            }
            else
            {
                obj["Status"] = "None";
            }
        }
        return obj;
    }

    Common::Turnout TurnoutSerializer::FromJson(const boost::json::object &obj)
    {
        Common::Turnout turnout;
        turnout.Id = obj.at("Id").as_int64();
        turnout.Address = obj.at("Address").as_int64();
        turnout.SubAddress = obj.at("SubAddress").as_int64();
        turnout.Pin = obj.at("Pin").as_int64();

        {
            std::map<std::string, StatusTurnout> helper_map
            {
                {"None",  StatusTurnout::StatusTurnout_None},
                {"Close", StatusTurnout::Close},
                {"Throw", StatusTurnout::Throw},
            };

            auto found = helper_map.find(std::string(obj.at("Status").as_string().c_str()));
            if (found != helper_map.end())
            {
                turnout.Status = (*found).second;
            }
            else
            {
                turnout.Status = StatusTurnout::StatusTurnout_None;
            }
        }

        return turnout;
    }
}
