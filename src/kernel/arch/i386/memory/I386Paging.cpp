#include "I386Paging.h"
#include "../cpu/I386Interrupt.h"
#include "../../../cpu/Interrupt.h"
#include "../../../../util/Mem.h"
#include "../../../io/KPrintf.h"
#include "../../../memory/KMalloc.h"
#include "../../../Panic.h"
#include "../../../Kernel.h"
#include "../../../io/Debug.h"

extern "C" void enable_paging(u32 page_directory);

namespace Memory{
    
    TrapInterruptServicePageFault trap_interrupt_service_page_fault;

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

        //CPU::register_interrupt(14, page_fault_handler, 0x08, 0x8E);
        CPU::register_interrupt(&trap_interrupt_service_page_fault);
        // first setup the available frames bitmap
        // for now assume we have only 4GB of memory
        num_frames = 0xEE6B2800/0x1000;
        frame_bitmap = (u32*)kmalloc_aligned(num_frames/32);
        // clear the bitmap
        memset(frame_bitmap, 0, num_frames/32);

        auto page_directory = create_kernel_page_directory();
        set_active_page_directory(page_directory);



        u32* page = get_page(page_directory, 0x0, false);

        //enable paging
        u32 cr0_value;
        asm volatile("mov %%cr0, %0": "=r"(cr0_value));
        cr0_value |= 0x80000000; // Enable paging!
        asm volatile("mov %0, %%cr0":: "r"(cr0_value));
        
        // enable 4MiB pages
        u32 cr4_value;
        asm volatile("mov %%cr4, %0": "=r"(cr4_value));
        cr4_value |= 0x00000010;
        asm volatile("mov %0, %%cr4":: "r"(cr4_value));

        IO::dbg() << "setup i386 paging\n";
    }

    void set_active_page_directory(PageDirectory* page_directory){
        // move the page directory into cr3
        asm volatile("mov %0, %%cr3":: "r"((u32)page_directory));
    }

    PageDirectory* create_page_directory(){
        PageDirectory* page_directory = (PageDirectory*)kmalloc_aligned(sizeof(PageDirectory));        // clear the page directory
        memset(page_directory, 0, sizeof(PageDirectory));
        for(u32 i=0;i<1024;i++){
            // set the page table to not present, kernel mode and r+w
            page_directory->page_tables[i] = 0x00000002;
        }
        return page_directory;
    }

    PageTable* create_page_table(){
        PageTable* page_table = (PageTable*)kmalloc_aligned(sizeof(PageTable));
        memset(page_table, 0, sizeof(PageTable));
        return page_table;
    }

    PageDirectory* create_kernel_page_directory(){
        PageDirectory* page_directory = create_page_directory();
        PageTable* page_table = create_page_table();
        for(u32 i=0;i<1024;i++){
            set_page_present(&page_table->pages[i], 1);
            set_page_rw(&page_table->pages[i], 1);
            set_page_frame(&page_table->pages[i], 0x1000 * i);
        }
        page_directory->page_tables[0]=(u32)page_table | 0x3;
        return page_directory;
    }

    // return a page from a given physical address
    u32* get_page(PageDirectory* page_directory, u32 physical_address, u1 make_if_not_found){
        // turn the physical address into a page index
        u32 page_index = physical_address/0x1000;
        // get the corresponding page table
        u32 page_table_index = page_index/1024;
        // if the page table exists, then return the page
        if(page_directory->page_tables[page_table_index]!=0){
            //PageTable* page_table = (PageTable*)page_directory->page_tables[page_table_index];
            u32 page_table_entry = page_directory->page_tables[page_table_index];
            // the actual page table address is the top 20 bits of the entry
            PageTable* page_table = (PageTable*)(page_table_entry & 0xFFFFF000);
            return &page_table->pages[page_index%1024];
        }else if(make_if_not_found){
            // create a page table and page entry in the directory
            // allocate the page table and get the physical address of it
            PageTable* page_table = (PageTable*)kmalloc_aligned(sizeof(u32)*1024);
            // now create a physical entry in the page directory
            page_directory->page_tables[page_table_index] = (u32)page_table | 0x3; // set the entry to present and r+w
            // return the page at the given page table
            return &page_table->pages[page_index%1024];
        }
        Kernel::panic(__FILE__, __LINE__, "cannot get page, doesn't exist and we are not creating it");
        return 0;
    }

    // allocate a frame for a page
    u1 alloc_frame(u32* page, u1 user, u1 wr){
        //!@TODO get_page_frame doesn't work
        // if the page has already been allocated a frame return
        if(get_page_frame(page)!=0){
            IO::kwarn("page frame allocation failed: frame already set\n");
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
        set_page_present(page, 1);
        set_page_rw(page, (wr==true)?1:0);
        set_page_usermode(page, (user==true)?1:0);
        set_page_frame(page, frame_index*0x1000);    
        return true;
    }

    // free a frame from a page
    u1 free_frame(u32* page){
        // if the page already free
        if(get_page_frame(page)==0)
            return false;
        clear_frame_used(get_page_frame(page));
        set_page_frame(page, 0);
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
                    if((frame_bitmap[j]&test_bit)==0){
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

    u32 get_page_present(u32* page){
        return *page & 0x1;
    }
    u32 get_page_rw(u32* page){
        return (*page & 0x2) >> 1;
    }
    u32 get_page_usermode(u32* page){
        return (*page & 0x4) >> 2;
    }
    u32 get_page_accessed(u32* page){
        return (*page & 0x8) >> 3;
    }
    u32 get_page_dirt(u32* page){
        return (*page & 0x16) >> 4;
    }
    u32 get_page_frame(u32* page){
        return (*page & 0xFFFFF000);
    }
    void set_page_present(u32* page, u32 value){
        *page |= value;
    }
    void set_page_rw(u32* page, u32 value){
        *page |= value << 1;
    }
    void set_page_usermode(u32* page, u32 value){
        *page |= value << 2;
    }
    void set_page_accessed(u32* page, u32 value){
        *page |= value << 3;
    }
    void set_page_dirt(u32* page, u32 value){
        *page |= value << 4;
    }
    void set_page_frame(u32* page, u32 value){
        *page |= value;
    }
}