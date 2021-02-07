#include "KMalloc.h"
#include "../io/KPrintf.h"

// defined in the linker script, this is the address after the entire kernel
// extern u32 end_of_kernel;

namespace Memory{

    u32 next_free_address = (u32)&end_of_kernel;

    // not aligned, and don't return the physical address
    u32 kmalloc(size size){
        // !@TODO align properly, e.g. if size was 5 bytes, then allocate 8 bytes to word align

        u32 addr = next_free_address;
        next_free_address+=size;
        IO::kinfo("kmalloc, size=");
        IO::kprint_int(size);
        IO::kprint_str(", addr= ");
        IO::kprint_int(addr);
        IO::kprint_c('\n');
        return addr;
    }

    u32 kmalloc_special(size size, u1 align, u1 physical, u32* physical_addr){


        // check if the next address is page aligned (4kb)
        if(align && (next_free_address&0x00000FFF)){
            // align the next address to a 4kb page
            next_free_address &= 0xFFFFF000;
            // then increase the next address by 4kb
            next_free_address += 0x1000;
        }
        // set the physical address
        if(physical)
            *physical_addr = next_free_address;
        // get the next address
        u32 addr = next_free_address;
        // finally increase the next address by the size requested
        next_free_address+=size;


        IO::kinfo("kmalloc=");
        IO::kprint_int(addr);
        IO::kprint_c('\n');
        return addr;
    }

    u32 kmalloc_aligned(size size){
        return kmalloc_special(size, true, false, 0);
    }

    u32 kmalloc_physical(size size, u32* physical_addr){
        return kmalloc_special(size, false, true, physical_addr);
    }

    u32 kmalloc_aligned__physical(size size, u32* physical_addr){
        return kmalloc_special(size, true, true, physical_addr);
    }

    void kfree(u32 ptr){
    }

}