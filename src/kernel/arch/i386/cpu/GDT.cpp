#include "GDT.h"

extern "C" void set_gdt(CPU::GDTDescriptor* gdt_descriptor);

CPU::GDTEntry gdt[5];
CPU::GDTDescriptor gdt_descriptor;

namespace CPU{


    u8 setup_gdt(){

        gdt_descriptor.limit = (sizeof(GDTEntry) * 5) - 1;
        gdt_descriptor.base = (u32)&gdt;

        add_entry(0, 0, 0, 0, 0); // null entry
        add_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code segment descriptor
        add_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data segment descriptor
        add_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user code segment descriptor
        add_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user data segment descriptor

        asm volatile ("lgdt %0" : : "m"(gdt_descriptor));
        //set_gdt(&gdt_descriptor);
        return 1;
    }

    void add_entry(u8 idx, u32 base, u32 limit, u8 access, u8 granularity){
        gdt[idx].base_low     = (base & 0xFFFF);
        gdt[idx].base_middle  = (base >> 16) & 0xFF;
        gdt[idx].base_high    = (base >> 24) & 0xFF;
        gdt[idx].limit_low    = (limit & 0xFFFF);
        gdt[idx].granularity  = (limit >> 16) & 0x0F;
        gdt[idx].granularity |= (granularity & 0xF0);
        gdt[idx].access       = access;
    }
}