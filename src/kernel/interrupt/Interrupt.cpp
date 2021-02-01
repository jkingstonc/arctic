#include "Interrupt.h"
#include "../KPrintf.h"
#include "../io/Port.h"


extern "C" void set_idt(u32* base, u32 limit);
extern u32 keyboard_interrupt;


extern "C" void keyboard_interrupt_handler(){
    IO::kprintf("keyboard pressed!");

    u8 c = IO::inb(0x60);
    IO::kprint_c(c);

    // signal finish interrupt
    IO::outb(0x20, 0x20);
    IO::outb(0xA0, 0x20);

}

namespace Interrupt{

    IDT idt;
    IDTDescriptor idt_descriptor;

    u8 setup_interrupts(){
        for (u32 i = 0; i<256; i++){
            add_entry(i, {
                .offset_low=(u16)(keyboard_interrupt & 0x0000FFFF),
                .selector=0x8,
                .zero=0,
                .type_attr=0b10101110,
                .offset_high=(u16)(keyboard_interrupt&0xFFFF0000 >> 4)
                });
        }
        IO::outb(0x21, 0xFD);
        IO::outb(0xA1,0xFF);
        install_idt();
        return 1;
    }

    IDT& create_idt(){
        idt = {};
        return idt;
    }

    IDT& add_entry(u32 idx, IDTEntry entry){
        idt.entries[idx]=entry;
        return idt;
    }

    void install_idt(){
        set_idt((u32*)&idt, sizeof(idt)-1);
    }
}