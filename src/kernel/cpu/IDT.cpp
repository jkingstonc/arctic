#include "IDT.h"
#include "Interrupt.h"
#include "../KPrintf.h"
#include "../io/Port.h"



extern "C" void set_idt(CPU::IDTDescriptor* idt_descriptor);

extern "C" void irq();

extern "C" void irq_handler(){
    keyboard_handler();
    return;
}


CPU::IDTEntry idt[256] = {0};
CPU::IDTDescriptor idt_descriptor;

namespace CPU{


    void remap_pic(){
        IO::outb(0x20, 0x11);
        IO::outb(0xA0, 0x11);
        IO::outb(0x21, 0x20);
        IO::outb(0xA1, 0x28);
        IO::outb(0x21, 0x04);
        IO::outb(0xA1, 0x02);
        IO::outb(0x21, 0x01);
        IO::outb(0xA1, 0x01);
        IO::outb(0x21, 0x0);
        IO::outb(0xA1, 0x0);
        IO::kprintf("[INFO] remapped PIC\n");
    }

    u8 setup_interrupts(){
        //add_entry(0, (u32)&irq, 0x08, 0x8E);
        add_entry(1, (u32)&irq, 0x08, 0x8E);
        add_entry(2, (u32)&irq, 0x08, 0x8E);
        add_entry(3, (u32)&irq, 0x08, 0x8E);
        add_entry(4, (u32)&irq, 0x08, 0x8E);
        add_entry(5, (u32)&irq, 0x08, 0x8E);
        add_entry(6, (u32)&irq, 0x08, 0x8E);
        add_entry(7, (u32)&irq, 0x08, 0x8E);
        add_entry(8, (u32)&irq, 0x08, 0x8E);
        add_entry(9, (u32)&irq, 0x08, 0x8E);
        add_entry(10, (u32)&irq, 0x08, 0x8E);
        add_entry(11, (u32)&irq, 0x08, 0x8E);
        add_entry(12, (u32)&irq, 0x08, 0x8E);
        add_entry(13, (u32)&irq, 0x08, 0x8E);
        add_entry(14, (u32)&irq, 0x08, 0x8E);
        add_entry(15, (u32)&irq, 0x08, 0x8E);
        add_entry(16, (u32)&irq, 0x08, 0x8E);
        add_entry(17, (u32)&irq, 0x08, 0x8E);
        add_entry(18, (u32)&irq, 0x08, 0x8E);
        add_entry(19, (u32)&irq, 0x08, 0x8E);
        add_entry(20, (u32)&irq, 0x08, 0x8E);
        add_entry(21, (u32)&irq, 0x08, 0x8E);
        add_entry(22, (u32)&irq, 0x08, 0x8E);
        add_entry(23, (u32)&irq, 0x08, 0x8E);
        add_entry(24, (u32)&irq, 0x08, 0x8E);
        add_entry(25, (u32)&irq, 0x08, 0x8E);
        add_entry(26, (u32)&irq, 0x08, 0x8E);
        add_entry(27, (u32)&irq, 0x08, 0x8E);
        add_entry(28, (u32)&irq, 0x08, 0x8E);
        add_entry(29, (u32)&irq, 0x08, 0x8E);
        add_entry(30, (u32)&irq, 0x08, 0x8E);
        add_entry(31, (u32)&irq, 0x08, 0x8E);
        add_entry(32, (u32)&irq, 0x08, 0x8E);
        add_entry(33, (u32)&irq, 0x08, 0x8E);
        add_entry(34, (u32)&irq, 0x08, 0x8E);
        add_entry(35, (u32)&irq, 0x08, 0x8E);
        add_entry(36, (u32)&irq, 0x08, 0x8E);
        add_entry(37, (u32)&irq, 0x08, 0x8E);
        add_entry(38, (u32)&irq, 0x08, 0x8E);
        add_entry(39, (u32)&irq, 0x08, 0x8E);
        add_entry(40, (u32)&irq, 0x08, 0x8E);
        add_entry(41, (u32)&irq, 0x08, 0x8E);
        add_entry(42, (u32)&irq, 0x08, 0x8E);
        add_entry(43, (u32)&irq, 0x08, 0x8E);
        add_entry(44, (u32)&irq, 0x08, 0x8E);
        add_entry(45, (u32)&irq, 0x08, 0x8E);
        add_entry(46, (u32)&irq, 0x08, 0x8E);
        add_entry(47, (u32)&irq, 0x08, 0x8E);
        // add_entry(0, (u32)&exc_0, 0x08, 0x8E);
        // add_entry(1, (u32)&keyboard_handler, 0x08, 0x8E);
        // add_entry(2, (u32)&exc_2, 0x08, 0x8E);
        // add_entry(3, (u32)&exc_3, 0x08, 0x8E);
        // add_entry(4, (u32)&exc_4, 0x08, 0x8E);
        // add_entry(5, (u32)&exc_5, 0x08, 0x8E);
        // add_entry(6, (u32)&exc_6, 0x08, 0x8E);
        // add_entry(7, (u32)&exc_7, 0x08, 0x8E);
        // add_entry(8, (u32)&exc_8, 0x08, 0x8E);
        // add_entry(9, (u32)&exc_9, 0x08, 0x8E);
        // add_entry(10, (u32)&exc_10, 0x08, 0x8E);
        // add_entry(11, (u32)&exc_11, 0x08, 0x8E);
        // add_entry(12, (u32)&exc_12, 0x08, 0x8E);
        // add_entry(13, (u32)&exc_13, 0x08, 0x8E);
        // add_entry(14, (u32)&exc_14, 0x08, 0x8E);
        // add_entry(15, (u32)&exc_15, 0x08, 0x8E);
        // add_entry(16, (u32)&exc_16, 0x08, 0x8E);
        // add_entry(17, (u32)&exc_17, 0x08, 0x8E);
        // add_entry(18, (u32)&exc_18, 0x08, 0x8E);
        // add_entry(19, (u32)&exc_19, 0x08, 0x8E);
        // add_entry(20, (u32)&exc_20, 0x08, 0x8E);
        // add_entry(30, (u32)&exc_30, 0x08, 0x8E);
        // add_entry(31, (u32)&pit_handler, 0x08, 0x8E);
        // add_entry(32, (u32)&exc_1, 0x08, 0x8E);
        // for (int i = 0x23; i < 0x28; i++){
        //     add_entry(i, (u32)&isr_irq_master);
        // }
        // for (int j = 0x28; j < 0x2F; j++){
        //     add_entry(j, (u32)&isr_irq_slave);
        // }

        idt_descriptor.limit = (sizeof(IDTEntry)*256);
        idt_descriptor.base = (u32)&idt;

        remap_pic();
        asm volatile ("lidt %0" : : "m"(idt_descriptor));
        asm volatile ("sti");

        
        //set_idt(&idt_descriptor);

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