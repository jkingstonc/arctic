#include "Paging.h"
#include "../io/KPrintf.h"


Memory::PageDirectory page_directory;
Memory::PageTable page_table;
extern "C" void enable_paging(u32 page_directory);

namespace Memory{
    
    void setup_page_directory(){
        // first blank the page directory
        for(u32 i = 0;i<1024;i++){
            // this sets:
            // Supervisor = kernel mode (only we can access it (ring 0))
            // Write Enabled = r+w
            // Not present = true
            page_directory.entries[i]=0x00000002;
        }
    }

    void setup_page_table(){
        // map some memory for the kernel
        // here i = physical address
        // so we are mapping this page table to the start of physical memory
        for(u32 i =0;i<1024;i++){
            // as the address is page aligned we need 12 bits zerod which are used by attributes
            page_table.entries[i] = (i*0x1000) | 3;
        }
        // place this page table into the page directory
        page_directory.entries[0]=((u32)&page_table) | 3;
    }

    void setup_paging(){
        setup_page_directory();
        setup_page_table();
        enable_paging((u32)&page_directory);
        IO::kprintf("[INFO] enabled paging\n");
    }

    u32 virtual_to_physical(u32 address){
        // bits 31-22 are the offset into the page directory
        // bits 21-12 are the offset into the page table
        // bits 11-0 are the offset into the page
        u32 directory_offset = (address & 0xFFC00000) >> 22;
        u32 table_offset = (address & 0x3FF000) >> 12;
        u32 page_offset = (address & 0xFFF);
        return 0;
    }

    
    u32 physical_to_virtual(u32 address){
        return 0;
    }
}