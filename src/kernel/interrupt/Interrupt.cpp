#include "Interrupt.h"
#include "../KPrintf.h"
#include "../io/Port.h"


extern "C" void set_idt(u32 base);
extern u32 keyboard_interrupt;


extern "C" void keyboard_interrupt_handler(){
    IO::kprintf("keyboard pressed!");
    u8 c = IO::inb(0x60);
}

namespace Interrupt{

    IDTEntry idt[256];
    IDTDescriptor idt_descriptor;

    u8 setup_interrupts(){
        for (u32 i = 0; i<31; i++){
            add_entry(i, (u32)keyboard_interrupt, 0x08, 0x8E);
        }
        // // remap the PIC
        // IO::outb(0x20, 0x11);
        // IO::outb(0xA0, 0x11);
        // IO::outb(0x21, 0x20);
        // IO::outb(0xA1, 40);
        // IO::outb(0x21, 0x04);
        // IO::outb(0xA1, 0x02);
        // IO::outb(0x21, 0x01);
        // IO::outb(0xA1, 0x01);
        // IO::outb(0x21, 0x0);

        idt_descriptor.limit = (sizeof(IDTEntry)*256) - 1;
        idt_descriptor.base = (u32)&idt;
        install_idt();
        return 1;
    }

    void add_entry(u32 idx, u32 base, u16 selector, u8 flags){
        idt[idx].base_low  = base & 0xFFFF;
        idt[idx].base_high = (base>>16) & 0xFFFF;
        idt[idx].selector  = selector;
        idt[idx].zero      = 0;
        idt[idx].flags     = flags;
    }

    void install_idt(){
        set_idt((u32)&idt_descriptor);
    }
}