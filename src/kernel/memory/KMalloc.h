#pragma once

#include "../Types.h"

extern u32 end_of_kernel;

namespace Memory{    
    extern u32 next_free_address;
    extern u32 kmalloc(size size);
    extern u32 kmalloc_special(size size, u1 aligned, u1 physical, u32* physical_addr);
    extern u32 kmalloc_aligned(size size);
    extern u32 kmalloc_physical(size size, u32* physical_addr);
    extern u32 kmalloc_aligned__physical(size size, u32* physical_addr);
    extern void kfree(u32 ptr);
}