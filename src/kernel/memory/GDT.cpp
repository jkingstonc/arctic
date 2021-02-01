#include "GDT.h"

extern "C" void set_gdt(u32* base, u32 limit);

namespace Memory{



    GDT gdt;

    u8 setup_gdt(){
        add_entry(0, 0, 0xFFFFFFFF, 0x00); // null entry
        add_entry(1, 0, 0xFFFFFFFF, 0x9A); // code segment descriptor
        add_entry(2, 0, 0xFFFFFFFF, 0x92); // data segment descriptor
        add_entry(3, 0, 0xFFFFFFFF, 0x89); // task state segment descriptor
        return 1;
    }

    void install_gdt(GDT gdt){
        set_gdt((u32*)&gdt, sizeof(gdt)-1);
    }

    GDT& add_entry(u32 idx, u32 base, u32 limit, u16 flag){
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