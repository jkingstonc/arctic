#include "GDT.h"

extern "C" void set_gdt(u32 descriptor);

namespace GDT{

    GDTEntry gdt[4];
    GDTDescriptor gdt_descriptor;

    u8 setup_gdt(){

        gdt_descriptor.limit = (sizeof(GDTEntry) * 4) - 1;
        gdt_descriptor.base = (u32)&gdt;

        add_entry(0, 0, 0, 0, 0); // null entry
        add_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code segment descriptor
        add_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data segment descriptor
        add_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // task state segment descriptor
        return 1;
    }

    void install_gdt(){
        set_gdt((u32)&gdt_descriptor);
    }

    void add_entry(u32 idx, u32 base, u32 limit, u8 access, u8 granularity){
        gdt[idx].base_low     = (base & 0xFFFF);
        gdt[idx].base_middle  = (base >> 16) & 0xFF;
        gdt[idx].base_high    = (base >> 24) & 0xFF;
        gdt[idx].limit_low    = (limit & 0xFFFF);
        gdt[idx].granularity  = (limit >> 16) & 0x0F;
        gdt[idx].granularity |= (granularity & 0xF0);
        gdt[idx].access       = access;
    }
}