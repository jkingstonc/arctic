#pragma once

#include "../Types.h"

namespace Memory {

    extern void memset(u0* ptr, u32 value, size size);
    // get the amount of available amount of memory the system has
    extern u32 get_available_memory();
}