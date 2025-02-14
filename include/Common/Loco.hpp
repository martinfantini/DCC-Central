#ifndef __COMMON_LOCO_INFORMATION_HPP__
#define __COMMON_LOCO_INFORMATION_HPP__

namespace Common
{
    enum LocoFunctionsGroup
    {
        LocoFunctionsGroup_None = 0,
        F1_F4,
        F5_F12,
        F13_F20,
        F21_F28,
    };

    enum SpeedStepsLabel
    {
        SpeedStepsLabel_None = 0,
        Steps_28,
        Steps_128,
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
        std::vector<unsigned char> FunctionStatus;
    };
}

#endif
