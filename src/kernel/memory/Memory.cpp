#include "Memory.h"
#include "GDT.h"
#include "../KPrintf.h"

namespace Memory{

    u8 setup_gdt(){
        IO::kprintf("setting up gdt...\n");
        // for now each gdt segment overlaps
        GDT gdt = create_gdt();
        add_entry(gdt, 0, 0, 0xFFFFFFFF, 0x00); // null entry
        add_entry(gdt, 1, 0, 0xFFFFFFFF, 0x9A); // code segment descriptor
        add_entry(gdt, 2, 0, 0xFFFFFFFF, 0x92); // data segment descriptor
        add_entry(gdt, 3, 0, 0xFFFFFFFF, 0x89); // task state segment descriptor
        // set the gdt in assembly
        install_gdt(gdt);
        return 1;
    }

    u64 get_memory_size(EFIMemoryMap* mem_map, u64 mem_map_entries, u64 mem_map_desc_size){
        u64 mem_size = 0;
        return mem_size;
    }
}