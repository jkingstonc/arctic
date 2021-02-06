#include "KMalloc.h"

namespace Memory{

    u32 next_address = 0x0;

    u32 kmalloc(size size, u1 align=0){
        // check if the next address is page aligned (4kb)
        if(align && (next_address&0xFFFF0000)){
            next_address &= 0xFFFF0000;
            next_address += 0x1000;
        }
        u32 addr = next_address;
        next_address+=size;
        return addr;
    }

    void kfree(u32 ptr){
    }

}