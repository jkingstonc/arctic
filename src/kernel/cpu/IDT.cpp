// #include "IDT.h"
// #include "Interrupt.h"
// #include "../io/KPrintf.h"
// #include "../io/Port.h"


// CPU::IDTEntry idt[256] = {0};
// CPU::IDTDescriptor idt_descriptor;

// namespace CPU{

//     void remap_pic_keyboard_only(){
//         IO::outb(0x21,0xfd);
//         IO::outb(0xa1,0xff);
//     }

//     void remap_pic(){
//         IO::outb(0x20, 0x11);
//         IO::outb(0xA0, 0x11);
//         IO::outb(0x21, 0x20);
//         IO::outb(0xA1, 0x28);
//         IO::outb(0x21, 0x04);
//         IO::outb(0xA1, 0x02);
//         IO::outb(0x21, 0x01);
//         IO::outb(0xA1, 0x01);
//         IO::outb(0x21, 0x0);
//         IO::outb(0xA1, 0x0);
//         IO::kinfo("remapped PIC\n");
//     }

//     u8 setup_idt(){
//         idt_descriptor.limit = (sizeof(IDTEntry)*256);
//         idt_descriptor.base = (u32)&idt;
//         remap_pic();
//         asm volatile ("lidt %0" : : "m"(idt_descriptor));
//         asm volatile ("sti");
//         return 1;
//     }

//     void add_entry(u32 idx, u32 base, u16 selector, u8 flags){
//         idt[idx].base_low  = base & 0xFFFF;
//         idt[idx].base_high = (base>>16) & 0xFFFF;
//         idt[idx].selector  = selector;
//         idt[idx].zero      = 0;
//         idt[idx].flags     = flags;
//     }
// }