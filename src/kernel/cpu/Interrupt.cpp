#include "Interrupt.h"
#include "../KPrintf.h"
#include "../io/Port.h"


extern "C" void set_idt(CPU::IDTDescriptor* idt_descriptor);

extern "C" void irq_handler(){
    IO::kprintf("IRQ!\n");
    IO::outb(0x20, 0x20);
    IO::outb(0xa0, 0x20);
}


extern "C" void irq1_handler(){
    u8 c = IO::inb(0x60);
    IO::kprintf("IRQ!\n");
    IO::outb(0x20, 0x20);
    IO::outb(0xa0, 0x20);
}

extern "C" s32 irq();
extern "C" s32 irq1();
u32 irq_address; 
u32 irq1_address; 

CPU::IDTEntry idt[256] = {0};
CPU::IDTDescriptor idt_descriptor;

namespace CPU{


    u8 setup_interrupts(){
        for (u32 i = 0; i<256; i++){
            irq_address = (u32)irq;
            add_entry(i, irq_address, 0x08, 0x8E);
        }
        irq1_address = (u32)irq1;
        add_entry(1, irq1_address, 0x08, 0x8E);

        idt_descriptor.limit = (sizeof(IDTEntry)*256) - 1;
        idt_descriptor.base = (u32)&idt;

        /* remapping the PIC */
	    IO::outb(0x20, 0x11);
        IO::outb(0xA0, 0x11);
        IO::outb(0x21, 0x20);
        IO::outb(0xA1, 40);
        IO::outb(0x21, 0x04);
        IO::outb(0xA1, 0x02);
        IO::outb(0x21, 0x01);
        IO::outb(0xA1, 0x01);
        IO::outb(0x21, 0x0);
        IO::outb(0xA1, 0x0);
        set_idt(&idt_descriptor);
        return 1;
    }

    void add_entry(u32 idx, u32 base, u16 selector, u8 flags){
        idt[idx].base_low  = base & 0xFFFF;
        idt[idx].base_high = (base>>16) & 0xFFFF;
        idt[idx].selector  = selector;
        idt[idx].zero      = 0;
        idt[idx].flags     = flags;
    }
}