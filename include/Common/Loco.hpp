#ifndef __COMMON_LOCO_INFORMATION_HPP__
#define __COMMON_LOCO_INFORMATION_HPP__

#include <vector>

namespace Common
{
    enum LocoFunctionsGroup
    {
        LocoFunctionsGroup_None = 0,
        F1_F4,
        F5_F12,
        F13_F20,
        F21_F28,
        LocoFunctionsGroup_Max, 
    };

    static bool LocoHasFunction(LocoFunctionsGroup FunctionIndicator, int FunctionNumber)
    {
        if (FunctionIndicator == LocoFunctionsGroup::F1_F4)
        {
            return (FunctionNumber > 0 && FunctionNumber < 5);
        }
        else if (FunctionIndicator == LocoFunctionsGroup::F5_F12)
        {
            return (FunctionNumber > 0 && FunctionNumber < 13);
        }
        else if (FunctionIndicator == LocoFunctionsGroup::F13_F20)
        {
            return (FunctionNumber > 0 && FunctionNumber < 21);
        }
        else if (FunctionIndicator == LocoFunctionsGroup::F21_F28)
        {
            return (FunctionNumber > 0 && FunctionNumber < 29);
        }
        return false;
    }

    enum SpeedStepsLabel
    {
        SpeedStepsLabel_None = 0,
        Steps_28 = 28,
        Steps_128 = 128,
    };

    struct Loco
    {
        //
        int Id;
        // 
        int Address;
        // store the actual speed
        int Speed = 0;
        // store the actual speed steps
        SpeedStepsLabel SpeedSteps = SpeedStepsLabel::SpeedStepsLabel_None;
        // store the current direction
        bool Direction = 0;
        // indictor of the group
        LocoFunctionsGroup FunctionIndicator = LocoFunctionsGroup::LocoFunctionsGroup_None;
        // current group value
        std::vector<unsigned char> FunctionStatus = { 0x00, 0x00, 0x00, 0x00 };
    };
}

#endif
