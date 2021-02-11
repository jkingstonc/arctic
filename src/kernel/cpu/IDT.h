// #pragma once

// #include "../Types.h"

// extern "C" void irq_timer();
// namespace CPU{

//     struct IDTEntry{
//         u16 base_low;
//         u16 selector;   // a code segment selector in GDT (typically 0x9A for code segment)
//         u8  zero;
//         u8  flags;
//         u16 base_high;
//     }__attribute__((packed));

//     struct IDTDescriptor{
//         u16 limit;
//         u32 base;
//     }__attribute__((packed));
    
//     extern u8 setup_idt();
//     extern void add_entry(u32 idx, u32 base, u16 selector, u8 flags);

// }

// extern CPU::IDTEntry idt[256];