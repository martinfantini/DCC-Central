#ifndef __COMMON_LOCO_HPP__
#define __COMMON_LOCO_HPP__

#include <cstddef>

struct Loco
{
    int locoId;
    int loco;
    char speedCode = 128; // 128
    char groupFlags = 0;
    unsigned long functions = 0;
};

#endif
