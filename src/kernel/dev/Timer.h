#pragma once



#include "../Types.h"


namespace Dev::Timer{
    extern void init_timer(u32 frequency);
    extern void timer_handler(u32 idx);
}