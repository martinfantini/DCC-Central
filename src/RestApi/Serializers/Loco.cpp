#include "Serializers/Loco.hpp"

#include <map>
#include <string>

namespace
{
    void FunctionF1_F4(boost::json::object& obj, unsigned char FunctionStatus)
    {
        for (int i = 1; i < 5; i++)
        {
            if ((FunctionStatus >> (i-1)) & 0x01)
            {
                obj["Function-" + std::to_string(i)] = true;
            }
            else
            {
                obj["Function-" + std::to_string(i)] = false;
            }
        }
    }

    void FunctionF5_F12(boost::json::object& obj, unsigned char FunctionStatus)
    {
        for (int i = 1; i < 5; i++)
        {
            if ((FunctionStatus >> (i-1)) & 0x01)
            {
                obj["Function-" + std::to_string(i+4)] = true;
            }
            else
            {
                obj["Function-" + std::to_string(i+4)] = false;
            }
        }
    }

    void FunctionF13_F20(boost::json::object& obj, unsigned char FunctionStatus)
    {
        for (int i = 1; i < 9; i++)
        {
            if ((FunctionStatus >> (i-1)) & 0x01)
            {
                obj["Function-" + std::to_string(i+12)] = true;
            }
            else
            {
                obj["Function-" + std::to_string(i+12)] = false;
            }
        }
    }

    void FunctionF21_F28(boost::json::object& obj, unsigned char FunctionStatus)
    {
        for (int i = 1; i < 9; i++)
        {
            if ((FunctionStatus >> (i-1)) & 0x01)
            {
                obj["Function-" + std::to_string(i+20)] = true;
            }
            else
            {
                obj["Function-" + std::to_string(i+20)] = false;
            }
        }
    }
}

namespace RestApi::Serializer
{
    using namespace Common;

    boost::json::object LocoSerializer::ToJson(const Common::Loco &loco)
    {
        boost::json::object obj;
        obj["Id"] = loco.Id;
        obj["Address"] = loco.Address;
        obj["Speed"] = loco.Speed;
        obj["Direction"] = loco.Direction;

        {
            static std::map<SpeedStepsLabel, std::string> helper_converter =
            {
                {SpeedStepsLabel::SpeedStepsLabel_None ,"None"},
                {SpeedStepsLabel::Steps_28  ,"28"},
                {SpeedStepsLabel::Steps_128 , "128"},
            };

            auto found = helper_converter.find(loco.SpeedSteps);
            if (found != helper_converter.end())
            {
                obj["SpeedSteps"] = (*found).second;
            }
            else
            {
                obj["SpeedSteps"] = "None";
            }
        }

        {
            static std::map<LocoFunctionsGroup, std::string> helper_converter =
            {
                {LocoFunctionsGroup::LocoFunctionsGroup_None    ,"None"},
                {LocoFunctionsGroup::F1_F4   ,"F1_F4"},
                {LocoFunctionsGroup::F5_F12  ,"F5_F12"},
                {LocoFunctionsGroup::F13_F20 ,"F13_F20"},
                {LocoFunctionsGroup::F21_F28 ,"F21_F28"},
            };

            auto found = helper_converter.find(loco.FunctionIndicator);
            if (found != helper_converter.end())
            {
                obj["FunctionIndicator"] =  (*found).second;
            }
            else
            {
                obj["FunctionIndicator"] = "None";
            }
        }

        if (loco.FunctionIndicator == LocoFunctionsGroup::F1_F4 && loco.FunctionStatus.size() > 0)
        {
            FunctionF1_F4(obj, loco.FunctionStatus[0]);
        }

        if (loco.FunctionIndicator == LocoFunctionsGroup::F5_F12 && loco.FunctionStatus.size() > 1)
        {
            FunctionF1_F4(obj, loco.FunctionStatus[0]);
            FunctionF5_F12(obj, loco.FunctionStatus[1]);
        }

        if (loco.FunctionIndicator == LocoFunctionsGroup::F13_F20 && loco.FunctionStatus.size() > 2)
        {
            FunctionF1_F4(obj, loco.FunctionStatus[0]);
            FunctionF5_F12(obj, loco.FunctionStatus[1]);
            FunctionF13_F20(obj, loco.FunctionStatus[2]);
        }

        if (loco.FunctionIndicator == LocoFunctionsGroup::F21_F28 && loco.FunctionStatus.size() > 3)
        {
            FunctionF1_F4(obj, loco.FunctionStatus[0]);
            FunctionF5_F12(obj, loco.FunctionStatus[1]);
            FunctionF13_F20(obj, loco.FunctionStatus[2]);
            FunctionF21_F28(obj, loco.FunctionStatus[3]);
        }

        return obj;
    }

    Common::Loco LocoSerializer::FromJson(const boost::json::object &obj)
    {
        Common::Loco Loco_result;
        Loco_result.Id = obj.at("Id").as_int64();
        Loco_result.Address = obj.at("Address").as_int64();
        Loco_result.Speed = obj.at("Speed").as_int64();
        Loco_result.Direction = obj.at("Direction").as_bool();

        {
            static std::map<std::string, SpeedStepsLabel> helper_converter =
            {
                {"None", SpeedStepsLabel::SpeedStepsLabel_None},
                {"28",   SpeedStepsLabel::Steps_28},
                {"128",  SpeedStepsLabel::Steps_128},
            };

            auto found = helper_converter.find(std::string(obj.at("SpeedSteps").as_string().c_str()));
            if (found != helper_converter.end())
            {
                Loco_result.SpeedSteps = (*found).second;
            }
            else
            {
                Loco_result.SpeedSteps = SpeedStepsLabel::SpeedStepsLabel_None;
            }
        }

        {
            static std::map<std::string, LocoFunctionsGroup> helper_converter =
            {
                {"None"    ,LocoFunctionsGroup::LocoFunctionsGroup_None},
                {"F1_F4"   ,LocoFunctionsGroup::F1_F4},
                {"F5_F12"  ,LocoFunctionsGroup::F5_F12},
                {"F13_F20" ,LocoFunctionsGroup::F13_F20},
                {"F21_F28" ,LocoFunctionsGroup::F21_F28},
            };

            auto found = helper_converter.find(std::string(obj.at("FunctionIndicator").as_string().c_str()));
            if (found != helper_converter.end())
            {
                Loco_result.FunctionIndicator = (*found).second;
            }
            else
            {
                Loco_result.FunctionIndicator = LocoFunctionsGroup::LocoFunctionsGroup_None;
            }
        }

        Loco_result.FunctionStatus = {0x00, 0x00, 0x00, 0x00};

        return Loco_result;
    }
}
