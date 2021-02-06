#include "Paging.h"
#include "../cpu/Interrupt.h"
#include "Memory.h"
#include "../io/KPrintf.h"
#include "KMalloc.h"
#include "../Panic.h"

Memory::PageDirectory page_directory;
Memory::PageTable page_table;
extern "C" void enable_paging(u32 page_directory);

namespace Memory{
    
    // bitmap of available frames
    // each bit is a used frame so we need to implement handling for each bit
    u32* frame_bitmap;
    // number of frames
    u32  num_frames = 0;
    // the main page directory for the kernel
    PageDirectory* kernel_page_directory;

    void page_fault_handler(CPU::Registers registers){

        // get the address of the page fault, stored in cr2
        u32 fault_addr;
        asm volatile("mov %%cr2, %0" : "=r" (fault_addr));

        IO::kerr("page fault, addr=");
        IO::kprint_int(fault_addr);
        IO::kprint_c('\n');

        CPU::end_of_interrupt(registers.int_no);
    }


    void setup_paging(){

        CPU::register_interrupt(14, page_fault_handler, 0x08, 0x8E);

        IO::kinfo("end of kernel address=");
        IO::kprint_int(next_free_kernel_address);
        IO::kprint_c('\n');


        // first setup the available frames bitmap
        // for now assume we have only 4GB of memory
        num_frames = 0xEE6B2800/0x1000;
        frame_bitmap = (u32*)kmalloc(num_frames/32);
        // clear the bitmap
        memset(frame_bitmap, 0, num_frames/32);

        IO::kinfo("available frames=");
        IO::kprint_int(num_frames);
        IO::kprint_c('\n');


        // create a page directory
        PageDirectory* page_directory = (PageDirectory*)kmalloc(sizeof(PageDirectory));
        // clear the page directory
        memset(page_directory, 0, sizeof(PageDirectory));


        // everything up to the next_free_kernel_address is in used and needs to be
        // identity mapped; mapped to itself. This is so we can transparently access
        // these memory locations
        u32 i = 0;
        while(i<next_free_kernel_address){
            // allocate a frame for the page for this address
            alloc_frame(get_page(page_directory, i, true), 0, 1);
        }


        // enable_paging((u32)page_directory);


        asm volatile("mov %0, %%cr3":: "r"(&page_directory->physical_address));
        u32 cr0_value;
        asm volatile("mov %%cr0, %0": "=r"(cr0_value));
        cr0_value |= 0x80000000; // Enable paging!
        asm volatile("mov %0, %%cr0":: "r"(cr0_value));
        IO::kprintf("[INFO] enabled paging\n");
    }


    // return a page from a given physical address
    Page* get_page(PageDirectory* page_directory, u32 physical_address, u1 make_if_not_found){

        // turn the physical address into a page index
        u32 page_index = physical_address/0x1000;
        // get the corresponding page table
        u32 page_table_index = page_index/1024;
        // if the page table exists, then return the page
        if(page_directory->page_tables[page_table_index]){
            return &page_directory->page_tables[page_table_index]->pages[page_index%1024];
        }else if(make_if_not_found){
            u32 physical_table_address;
            // create a page table and page entry in the directory
            // allocate the page table and get the physical address of it
            page_directory->page_tables[page_table_index] = (PageTable*)kmalloc_physical(sizeof(PageTable), &physical_table_address);
            // clear the page table
            memset(page_directory->page_tables[page_table_index], 0, 0x1000);
            // now create a physical entry in the page directory
            page_directory->physical_entries[page_table_index] = (physical_table_address | 0x7); // set the entry to present, read write and kernel space
            // return the page entry within the table
            return &page_directory->page_tables[page_table_index]->pages[page_index%1024];
        }
        return 0;
    }


    PageTable* get_page_table(PageDirectory* page_directory, u32 physical_address){
        // to get the table index, first divide by the frame size, then the number of frames per table
        u32 table_index = (physical_address/0x1000)/1024;
        if(page_directory->page_tables[table_index]==0)
            return 0;
        return page_directory->page_tables[table_index];
    }

    // allocate a frame for a page
    u1 alloc_frame(Page* page, u1 user, u1 wr){
        // if the page has already been allocated a frame return
        if(page->frame!=0){
            //IO::kwarn("page frame allocation failed: frame already set\n");
            return false;
        }
        // get the next free frame
        u32 frame_index = next_free_frame();
        if(frame_index==(u32)-1){
            Kernel::panic(__FILE__, __LINE__, "page frame allocation failed: no free frames left!\n");
            return false;
        }
        // claim the frame
        set_frame_used(frame_index*0x1000);
        page->frame=frame_index;
        page->present=1;
        page->rw=(wr==true)?1:0;
        page->user=(user==true)?1:0;
        IO::kinfo("allocated frame: ");
        IO::kprint_int(frame_index*0x1000);
        IO::kprint_c('\n');
        return true;
    }

    // free a frame from a page
    u1 free_frame(Page* page){
        // if the page already free
        if(page->frame==0)
            return false;
        clear_frame_used(page->frame*0x1000);
        page->frame=0;
        return true;
    }

    // return the next free frame address
    u32 next_free_frame(){
        for(u32 i = 0;i<num_frames/32;i++){
            // if this frame is full then move on
            if(frame_bitmap[i] != 0xFFFFFFFF){
                // iterate through each bit to find a free bit
                for(u32 j = 0;j<32; j++){
                    u32 test_bit = 0x1 << j;
                    // check if its 0 (free!)
                    if(!(frame_bitmap[j]&test_bit)){
                        return i*32+j;
                    }
                }
            }
        }
        return (u32)-1;
    }
        // set a frame as used
    void set_frame_used(u32 frame_address){
        // get the frame index
        u32 frame = frame_address/0x1000;
        u32 index = frame/32;
        // get the bit offset
        u32 bit_offset = frame%32;
        // set the bit to 1
        frame_bitmap[index] |= (0x1 << bit_offset);
    }
    // test if a frame is used
    u8 test_frame_used(u32 frame_address){
        // get the frame index
        u32 frame = frame_address/0x1000;
        u32 index = frame/32;
        // get the bit offset
        u32 bit_offset = frame%32;
        // return if the bit is 0
        return (frame_bitmap[index] & (0x1 << bit_offset));
    }
    // clear a used frame
    void clear_frame_used(u32 frame_address){
                // get the frame index
        u32 frame = frame_address/0x1000;
        u32 index = frame/32;
        // get the bit offset
        u32 bit_offset = frame%32;
        // set the bit to 0
        frame_bitmap[index] &= (0x1 << bit_offset);
    }
}