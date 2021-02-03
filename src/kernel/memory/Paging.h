#pragma once

#include "../Types.h"

namespace Memory{

    // each page is 4Mib (4194304 bytes)
    struct Page{
        u32 memory[4194304];
    }__attribute__((packed));

    // contains an array of pages
    struct PageTable{
        u32 entries[1024];
    }__attribute__((packed)) __attribute__((aligned(4096)));

    // contains an array of page tables
    struct PageDirectory{
        u32 entries[1024];
    }__attribute__((packed)) __attribute__((aligned(4096)));

    extern void setup_paging();
    // convert a virtual address to physical
    extern u32 virtual_to_physical(u32 address);
    extern u32 physical_to_virtual(u32 address);
}