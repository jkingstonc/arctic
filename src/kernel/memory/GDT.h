#pragma once

#include "../Types.h"

namespace GDT {

    // 8 bytes long
    struct __attribute__((packed)) GDTEntry{
        u16 limit_low;
        u16 base_low;
        u8 base_middle;
        u8 access;      // what ring this segment can be used in
        u8 granularity;
        u8 base_high;
    };

    struct __attribute__((packed)) GDTDescriptor{
        u16 limit; // upper 16 bits of all selector limits
        u32 base;  // base address of the first GDTEntry
    };

    extern GDTEntry gdt[4];
    extern GDTDescriptor gdt_descriptor;

    extern u8 setup_gdt();
    extern void install_gdt();
    extern void add_entry(u32 idx, u32 base, u32 limit, u8 access, u8 granularity);

}