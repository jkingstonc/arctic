#include "GDT.h"

extern "C" void set_gdt(Memory::GDT gdt, u32 size);

namespace Memory{
    GDT create_gdt(){
        return {};
    }

    void install_gdt(GDT gdt){
        set_gdt(gdt, sizeof(gdt));
    }

    GDT& add_entry(GDT& gdt, u32 idx, u32 base, u32 limit, u16 flag){
        // first set the high part of the segment
        gdt.entries[idx].descriptor = limit         & 0x000F0000; // set limit bits 19:16
        gdt.entries[idx].descriptor |= (flag << 8)  & 0x00F0FF00; // set type
        gdt.entries[idx].descriptor |= (base >> 16) & 0x000000FF; // set base bits 23:16
        gdt.entries[idx].descriptor |= base         & 0xFF000000; // set base bits 31:24
        // shift by 32 to allow for low part of segment
        gdt.entries[idx].descriptor <<= 32;
        gdt.entries[idx].descriptor |= base << 16;         // set base bits 15:0
        gdt.entries[idx].descriptor |= limit & 0x0000FFFF; // set limit bits 15:0
        return gdt;
    }
}