#pragma once

#include <kernel/Kernel.h>
#include <util/OrderedVector.h>
#include <kernel/memory/Heap.h>

namespace Memory{    
    extern Heap* kernel_heap;
    extern u32 next_free_address;
    extern u32 end_of_kernel_address;
    extern u32 kmalloc(size size);
    extern u32 krealloc(u32 data, size size);
    extern u32 kmalloc_special(size size, u1 aligned, u1 physical, u32* physical_addr);
    extern u32 kmalloc_aligned(size size);
    extern u32 kmalloc_physical(size size, u32* physical_addr);
    extern u32 kmalloc_aligned__physical(size size, u32* physical_addr);
    extern void kfree(u32 ptr);
    extern void setup_kernel_heap();
}