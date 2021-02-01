#pragma once

#include "../Types.h"

namespace Interrupt{

    struct __attribute__((packed)) IDTEntry{
        u16 base_low;
        u16 selector;   // a code segment selector in GDT (typically 0x9A for code segment)
        u8  zero;
        u8  flags;
        u16 base_high;
    };

    struct __attribute__((packed)) IDTDescriptor{
        u16 limit;
        u32 base;
    };
    
    extern IDTEntry idt[256];
    extern IDTDescriptor idt_descriptor;
    extern u8 setup_interrupts();
    extern void add_entry(u32 idx, u32 base, u16 selector, u8 flags);
    void install_idt();

}