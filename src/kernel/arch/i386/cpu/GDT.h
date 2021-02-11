#pragma once

#include "../../../Types.h"

namespace CPU {

    // 8 bytes long
    struct GDTEntry{
        u16 limit_low;
        u16 base_low;
        u8 base_middle;
        u8 access;      // what ring this segment can be used in
        u8 granularity;
        u8 base_high;
    }__attribute__((packed));


    struct GDTDescriptor{
        u16 limit; // upper 16 bits of all selector limits
        u32 base;  // base address of the first GDTEntry
    }__attribute__((packed));


    extern u8 setup_gdt();
    extern void add_entry(u8 idx,u32 base, u32 limit, u8 access, u8 granularity);
}

extern CPU::GDTEntry gdt[5];
extern CPU::GDTDescriptor gdt_descriptor;