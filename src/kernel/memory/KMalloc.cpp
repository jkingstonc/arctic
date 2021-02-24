#include "KMalloc.h"
#include "../io/KPrintf.h"
#include <kernel/io/Debug.h>

// defined in the linker script, this is the address after the entire kernel
// extern u32 end_of_kernel;
extern u32 end_of_kernel;

namespace Memory{

    Heap* kernel_heap;
    u1 kernel_heap_ready;
    u32 next_free_address = (u32)&end_of_kernel;
    u32 end_of_kernel_address = (u32)&end_of_kernel;

    // not aligned, and don't return the physical address
    u32 kmalloc(size size){
        if(kernel_heap_ready){
            return kernel_heap->alloc(size);
        }
        // !@TODO word align properly by type size, e.g. if size was 5 bytes, then allocate 8 bytes to word align
        u32 addr = next_free_address;
        next_free_address+=size;
        return addr;
    }

    u32 krealloc(u32 data, size size){
        if(kernel_heap_ready){
            return kernel_heap->realloc(data, size);
        }
        return 0;
    }

    void kfree(u32 ptr){
        if(kernel_heap_ready){
            kernel_heap->free(ptr);
        }
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

    void setup_kernel_heap(){
        kernel_heap = (Heap*)kmalloc(sizeof(Heap));
        kernel_heap->setup(0xc00030, 0x10000);
        kernel_heap_ready=true;
    }

}