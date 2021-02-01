#pragma once

#include "../Types.h"

namespace Interrupt{

    struct IDTEntry{
        u16 offset_low;
        u16 selector;   // a code segment selector in GDT (typically 0x9A for code segment)
        u8  zero;
        u8  type_attr;
        u16 offset_high;
    };

    struct IDTDescriptor {
        u32 end;
        u64 start;
    };

    // Interrupt Descriptor Table
    struct IDT{
        IDTEntry entries[256];
    };

    extern IDT idt;
    extern u8 setup_interrupts();
    extern IDT& add_entry(u32 idx, IDTEntry entry);
    void install_idt();

}