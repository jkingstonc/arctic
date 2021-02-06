#pragma once

#include "../Types.h"

namespace Memory{
    extern u32 next_address;
    extern u32 kmalloc(size size, u1 align=0);
    extern void kfree(u32 ptr);
}