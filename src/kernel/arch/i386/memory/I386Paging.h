#pragma once

#include "../../../Types.h"
#include "../cpu/I386CPU.h"

namespace Memory{

    // // each page frame (not page entry!) is 4Mib (4194304 bytes)
    struct Page{
        u32 present  : 1;  // present in memory
        u32 rw       : 1;  // r if 0, r+w if 1
        u32 usermode : 1;  // kernel if 0, usermode if 1
        u32 accessed : 1;  // has the page been accessed since last refresh
        u32 dirty    : 1;  // has the page been written to since last refresh
        u32 unused   : 7;  // unused and reserve bits
        u32 frame    : 20; // page frame address (each page frame is 4Mib)
    } __attribute__((packed));



    extern u32 get_page_present(u32* page);
    extern u32 get_page_rw(u32* page);
    extern u32 get_page_usermode(u32* page);
    extern u32 get_page_accessed(u32* page);
    extern u32 get_page_dirt(u32* page);
    extern u32 get_page_frame(u32* page);
    extern void set_page_present(u32* page, u32 value);
    extern void set_page_rw(u32* page, u32 value);
    extern void set_page_usermode(u32* page, u32 value);
    extern void set_page_accessed(u32* page, u32 value);
    extern void set_page_dirt(u32* page, u32 value);
    extern void set_page_frame(u32* page, u32 value);


    struct PageTable{
        u32 pages[1024];
    } __attribute__((aligned(4096)));
    // contains an array of page tables
    struct PageDirectory{
        // physical addresses of the page table entries
        u32 page_tables[1024];
    }  __attribute__((aligned(4096)));


    // bitmap of available frames
    extern u32* frame_bitmap;
    // number of frames
    extern u32  num_frames;
    // the main page directory for the kernel
    extern PageDirectory* kernel_page_directory;

    extern void page_fault_handler(CPU::Registers registers);
    extern PageDirectory* create_page_directory();
    extern PageTable* create_page_table();
    extern PageDirectory* create_kernel_page_directory();
    extern void set_active_page_directory(PageDirectory* page_directory);


    // return a pointer to a page
    extern u32* get_page(PageDirectory* page_directory, u32 physical_address, u1 make_if_not_found);

    // allocate a frame for a page
    extern u1 alloc_frame(u32* page, u1 user, u1 wr);
    // free a frame from a page
    extern u1 free_frame(u32* page);
    // return the next free frame address
    extern u32 next_free_frame();
    // set a frame as used
    extern void set_frame_used(u32 frame_address);
    // test if a frame is used
    extern u8 test_frame_used(u32 frame_address);
    // clear a used frame
    extern void clear_frame_used(u32 frame_address);

}