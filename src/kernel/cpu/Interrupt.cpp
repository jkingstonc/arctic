#include "Interrupt.h"
#include "../KPrintf.h"
#include "../io/Port.h"
#include "../dev/Keyboard.h"

namespace CPU{

    const char* exception_types[31] = {
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
        "Security Exception"
    };

    void handle_exception(const char* exception) {
        IO::kprintf("[EXCEPTION] ");
        IO::kprintf(exception);
        IO::kprintf("\n");
    }
}


void exc_0(){ CPU::handle_exception(CPU::exception_types[0]);}
void exc_1(){ CPU::handle_exception(CPU::exception_types[1]);}
void exc_2(){ CPU::handle_exception(CPU::exception_types[2]);}
void exc_3(){ CPU::handle_exception(CPU::exception_types[3]);}
void exc_4(){ CPU::handle_exception(CPU::exception_types[4]);}
void exc_5(){ CPU::handle_exception(CPU::exception_types[5]);}
void exc_6(){ CPU::handle_exception(CPU::exception_types[6]);}
void exc_7(){ CPU::handle_exception(CPU::exception_types[7]);}
void exc_8(){ CPU::handle_exception(CPU::exception_types[8]);}
void exc_9(){ CPU::handle_exception(CPU::exception_types[9]);}
void exc_10(){CPU::handle_exception(CPU::exception_types[10]);}
void exc_11(){CPU::handle_exception(CPU::exception_types[11]);}
void exc_12(){CPU::handle_exception(CPU::exception_types[12]);}
void exc_13(){CPU::handle_exception(CPU::exception_types[13]);}
void exc_14(){CPU::handle_exception(CPU::exception_types[14]);}
void exc_15(){CPU::handle_exception(CPU::exception_types[15]);}
void exc_16(){CPU::handle_exception(CPU::exception_types[16]);}
void exc_17(){CPU::handle_exception(CPU::exception_types[17]);}
void exc_18(){CPU::handle_exception(CPU::exception_types[18]);}
void exc_19(){CPU::handle_exception(CPU::exception_types[19]);}
void exc_20(){CPU::handle_exception(CPU::exception_types[20]);}
void exc_30(){CPU::handle_exception(CPU::exception_types[21]);}
extern void pit_handler(){
    IO::kprintf("pit handler\n");
}

extern void keyboard_handler(){

    // KEYBOARD IN PORT     = 0X60
    // KEYBOARD STATUS PORT = 0x64

    // read from the keyboard in port
    const u8 status = IO::inb(0x64);
	const u8 scancode = IO::inb(0x60);
	/* Lowest bit of status will be set if buffer is not empty */
	if (status & 0x01) {
		if(scancode > 0)
            IO::kprint_c(Dev::Keyboard::keyboard_map[scancode]);
	}
    // signal end of interrupt
    IO::outb(0x20, 0x20);
    IO::outb(0xA0, 0x20);
    return;
}