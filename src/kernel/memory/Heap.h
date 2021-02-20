#pragma once

#include <kernel/Kernel.h>
#include <util/OrderedVector.h>

namespace Memory{

    #define HEAP_MAX_ENTRY    0xc000 // max number of entries in the heap entry vector
    #define HEAP_ENTRY_MAGIC  0x99123
    #define HEAP_ENTRY_FULL   0x1
    #define HEAP_ENTRY_HOLE   0x0
    #define HEAP_ENTRY_HEADER 0x1
    #define HEAP_ENTRY_FOOTER 0x0

    struct HeapEntryBoundary{
        u32 magic = HEAP_ENTRY_MAGIC;
        u32 size  = 0;                  // size of the block EXCLUDING the boundaries
        u8  hole  = HEAP_ENTRY_HOLE;
        u8  mode  = HEAP_ENTRY_HEADER;

        friend u1 operator<(HeapEntryBoundary& first, HeapEntryBoundary& second);
    };

    extern u1 operator<(HeapEntryBoundary& first, HeapEntryBoundary& second);

    class Heap{
    public:
        Heap();
        ~Heap();
        void setup(u32 start_addr, u32 size);
        u32 alloc(u32 size, u1 page_align=false);
        void free(u32 addr);
        void debug();
    private:
        s32 find_smallest_hole(u32 size, u1 page_align);
        u32 m_start_addr;     // start of the heap
        u32 m_end_addr;       // end of the heap
        u32 m_max_arrd;       // heap max
        u1  m_supervisor_mode;
        u1  m_readonly;
        OrderedVector<u32> m_allocation_map;
    };
}