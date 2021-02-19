#pragma once

#include <kernel/Kernel.h>
#include <util/OrderedVector.h>

namespace Memory{
    class Heap{
    public:
        u32 alloc(u32 size, u1 page_align);
        void free(u32 addr);
    private:
        u32 m_start_addr;     // start of the heap
        u32 m_end_addr;       // end of the heap
        u32 m_max_arrd;       // heap max
        u1  m_supervisor_mode;
        u1  m_readonly;
        OrderedVector<u32> m_allocation_map;
    };
}