#pragma once

#include "../Types.h"
#include "../cpu/CPU.h"

namespace Memory{

    // each page frame (not page entry!) is 4Mib (4194304 bytes)
    struct Page{
        u32 present  : 1;  // present in memory
        u32 rw       : 1;  // r if 0, r+w if 1
        u32 user     : 1;  // kernel or usermode
        u32 accessed : 1;  // has the page been accessed since last refresh
        u32 dirty    : 1;  // has the page been written to since last refresh
        u32 unused   : 7;  // unused and reserve bits
        u32 frame    : 20; // page frame address (each page frame is 4Mib)
    }__attribute__((packed));

    // contains an array of pages
    struct PageTable{
        Page pages[1024];
    }__attribute__((packed)) __attribute__((aligned(4096)));

    // contains an array of page tables
    struct PageDirectory{
        // physical addresses of the page table entries
        PageTable* page_tables[1024];
        // virtual addresses to the page table entries
        // this allows us to not map the page directory address to itself which is a bit of a pain bc
        // the address of the page directory would be weird like 0x40001000
        u32        physical_entries[1024];
        // physical address of this page directory, again so we don't have to virtually map it
        u32        physical_address;
    }__attribute__((packed)) __attribute__((aligned(4096)));


    // bitmap of available frames
    extern u32* frame_bitmap;
    // number of frames
    extern u32  frame_counter;
    // the main page directory for the kernel
    extern PageDirectory* kernel_page_directory;

    extern void page_fault_handler(CPU::Registers registers);
    extern void setup_paging();

    // return a page from a given physical address
    extern Page* get_page(PageDirectory* page_directory, u32 physical_address, u1 make_if_not_found);
    extern PageTable* get_page_table(PageDirectory* page_directory, u32 physical_address);

    // allocate a frame for a page
    extern u1 alloc_frame(Page* page, u1 user, u1 wr);
    // free a frame from a page
    extern u1 free_frame(Page* page);
    // return the next free frame address
    extern u32 next_free_frame();
    // set a frame as used
    extern void set_frame_used(u32 frame_address);
    // test if a frame is used
    extern u8 test_frame_used(u32 frame_address);
    // clear a used frame
    extern void clear_frame_used(u32 frame_address);

}