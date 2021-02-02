#include "Interrupt.h"
#include "../KPrintf.h"
#include "../io/Port.h"
#include "../dev/Keyboard.h"


extern "C" void exec_0(){ CPU::handle_exception(CPU::exception_types[0]);}
extern "C" void exec_1(){ CPU::handle_exception(CPU::exception_types[1]);}
extern "C" void exec_2(){ CPU::handle_exception(CPU::exception_types[2]);}
extern "C" void exec_3(){ CPU::handle_exception(CPU::exception_types[3]);}
extern "C" void exec_4(){ CPU::handle_exception(CPU::exception_types[4]);}
extern "C" void exec_5(){ CPU::handle_exception(CPU::exception_types[5]);}
extern "C" void exec_6(){ CPU::handle_exception(CPU::exception_types[6]);}
extern "C" void exec_7(){ CPU::handle_exception(CPU::exception_types[7]);}
extern "C" void exec_8(){ CPU::handle_exception(CPU::exception_types[8]);}
extern "C" void exec_9(){ CPU::handle_exception(CPU::exception_types[9]);}
extern "C" void exec_10(){CPU::handle_exception(CPU::exception_types[10]);}
extern "C" void exec_11(){CPU::handle_exception(CPU::exception_types[11]);}
extern "C" void exec_12(){CPU::handle_exception(CPU::exception_types[12]);}
extern "C" void exec_13(){CPU::handle_exception(CPU::exception_types[13]);}
extern "C" void exec_14(){CPU::handle_exception(CPU::exception_types[14]);}
extern "C" void exec_15(){CPU::handle_exception(CPU::exception_types[15]);}
extern "C" void exec_16(){CPU::handle_exception(CPU::exception_types[16]);}
extern "C" void exec_17(){CPU::handle_exception(CPU::exception_types[17]);}
extern "C" void exec_18(){CPU::handle_exception(CPU::exception_types[18]);}
extern "C" void exec_19(){CPU::handle_exception(CPU::exception_types[19]);}

namespace CPU{

    const char* exception_types[20] = {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Arithmetic Overflow",
        "Bound Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Invalid TSS",
        "Segment Not Present",
        "Stack Exception",
        "General Protection Fault",
        "Page Fault",
        "x87 Floating Point Exception",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating Point Exception",
        "Virtualisation Exception",
        "Control Protection Exception Exception"
    };

    void handle_exception(const char* exception) {
        IO::kprintf("[EXCEPTION] ");
        IO::kprintf(exception);
        IO::kprintf("\n");
    }
    
    void end_of_interrupt(u32 idx){
        if(idx>=8){
            IO::outb(0xA0, 0x20);
        }
        IO::outb(0x20, 0x20);
    }

    void set_irq_mask(u32 idx){
        u16 port;
        u8 value;
    
        if(idx < 8) {
            port = 0x21;
        } else {
            port = 0xA1;
            idx -= 8;
        }
        value = IO::inb(port) | (1 << idx);
        IO::outb(port, value);  
    }

    void clear_irq_mask(u32 idx){
        u16 port;
        u8 value;
    
        if(idx < 8) {
            port = 0x21;
        } else {
            port = 0xA1;
            idx -= 8;
        }
        value = IO::inb(port) & ~(1 << idx);
        IO::outb(port, value);  
    }
}