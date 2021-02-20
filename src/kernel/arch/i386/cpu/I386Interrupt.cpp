#include "I386Interrupt.h"
#include "../../../io/KPrintf.h"
#include "../../../io/Port.h"
#include "../../../dev/Keyboard.h"
#include "../../../io/Debug.h"
#include "I386IDT.h"

// universal interrupt wrapper function
extern "C" void interrupt_handler(CPU::Registers registers){
    
    
    // // call the required interrupt
    // CPU::interrupts[registers.int_no](registers);
    // call the required interrupt handler
    CPU::interrupts_v2[registers.int_no]->interrupt_handler(registers);
    
    return;
}

// universal interrupt wrapper function
extern "C" void interrupt_handler_v2(CPU::Registers registers){
    // call the required interrupt handler
    CPU::interrupts_v2[registers.int_no]->interrupt_handler(registers);
    return;
}


extern "C" void interrupt_isr_0();
extern "C" void interrupt_isr_1();
extern "C" void interrupt_isr_2();
extern "C" void interrupt_isr_3();
extern "C" void interrupt_isr_4();
extern "C" void interrupt_isr_5();
extern "C" void interrupt_isr_6();
extern "C" void interrupt_isr_7();
extern "C" void interrupt_isr_err_8();
extern "C" void interrupt_isr_9();
extern "C" void interrupt_isr_err_10();
extern "C" void interrupt_isr_err_11();
extern "C" void interrupt_isr_err_12();
extern "C" void interrupt_isr_err_13();
extern "C" void interrupt_isr_err_14();
extern "C" void interrupt_isr_15();
extern "C" void interrupt_isr_16();
extern "C" void interrupt_isr_err_17();
extern "C" void interrupt_isr_18();
extern "C" void interrupt_isr_19();
extern "C" void interrupt_isr_20();
extern "C" void interrupt_isr_21();
extern "C" void interrupt_isr_22();
extern "C" void interrupt_isr_23();
extern "C" void interrupt_isr_24();
extern "C" void interrupt_isr_25();
extern "C" void interrupt_isr_26();
extern "C" void interrupt_isr_27();
extern "C" void interrupt_isr_28();
extern "C" void interrupt_isr_29();
extern "C" void interrupt_isr_err_30();
extern "C" void interrupt_isr_31();
extern "C" void interrupt_isr_32();
extern "C" void interrupt_isr_33();
extern "C" void interrupt_isr_34();
extern "C" void interrupt_isr_35();



// setup the trap interrupt services
CPU::TrapInterruptService0 trap_interrupt_service_0;
CPU::TrapInterruptService1 trap_interrupt_service_1;
CPU::TrapInterruptService2 trap_interrupt_service_2;
CPU::TrapInterruptService3 trap_interrupt_service_3;
CPU::TrapInterruptService4 trap_interrupt_service_4;
CPU::TrapInterruptService5 trap_interrupt_service_5;
CPU::TrapInterruptService6 trap_interrupt_service_6;
CPU::TrapInterruptService7 trap_interrupt_service_7;
CPU::TrapInterruptService8 trap_interrupt_service_8;
CPU::TrapInterruptService9 trap_interrupt_service_9;
CPU::TrapInterruptService10 trap_interrupt_service_10;
CPU::TrapInterruptService11 trap_interrupt_service_11;
CPU::TrapInterruptService12 trap_interrupt_service_12;
CPU::TrapInterruptService13 trap_interrupt_service_13;
CPU::TrapInterruptService14 trap_interrupt_service_14;
CPU::TrapInterruptService15 trap_interrupt_service_15;
CPU::TrapInterruptService16 trap_interrupt_service_16;
CPU::TrapInterruptService17 trap_interrupt_service_17;
CPU::TrapInterruptService18 trap_interrupt_service_18;
CPU::TrapInterruptService19 trap_interrupt_service_19;
CPU::TrapInterruptService20 trap_interrupt_service_20;
CPU::TrapInterruptService21 trap_interrupt_service_21;
CPU::TrapInterruptService22 trap_interrupt_service_22;
CPU::TrapInterruptService23 trap_interrupt_service_23;
CPU::TrapInterruptService24 trap_interrupt_service_24;
CPU::TrapInterruptService25 trap_interrupt_service_25;
CPU::TrapInterruptService26 trap_interrupt_service_26;
CPU::TrapInterruptService27 trap_interrupt_service_27;
CPU::TrapInterruptService28 trap_interrupt_service_28;
CPU::TrapInterruptService29 trap_interrupt_service_29;

namespace CPU{

    void (*interrupts[256])(Registers);
    InterruptService* interrupts_v2[256];

    void (*interrupts_isrs[])() = {
        interrupt_isr_0,
        interrupt_isr_1,
        interrupt_isr_2,
        interrupt_isr_3,
        interrupt_isr_4,
        interrupt_isr_5,
        interrupt_isr_6,
        interrupt_isr_7,
        interrupt_isr_err_8,
        interrupt_isr_9,
        interrupt_isr_err_10,
        interrupt_isr_err_11,
        interrupt_isr_err_12,
        interrupt_isr_err_13,
        interrupt_isr_err_14,
        interrupt_isr_15,
        interrupt_isr_16,
        interrupt_isr_err_17,
        interrupt_isr_18,
        interrupt_isr_19,
        interrupt_isr_20,
        interrupt_isr_21,
        interrupt_isr_22,
        interrupt_isr_23,
        interrupt_isr_24,
        interrupt_isr_25,
        interrupt_isr_26,
        interrupt_isr_27,
        interrupt_isr_28,
        interrupt_isr_29,
        interrupt_isr_err_30,
        interrupt_isr_31,
        interrupt_isr_32,
        interrupt_isr_33,
        interrupt_isr_34,
        interrupt_isr_35,
    };

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
        "Coprosessor Segment Overrun",
        "Invalid TSS",
        "Segment Not Present",
        "Stack-Segment Fault",
        "General Protection Fault",
        "Page Fault",
        "Reserved",
        "x87 Floating Point Exception",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating Point Exception",
        "Virtualisation Exception",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Triple Fault"
    };

    void handle_exception(const char* exception) {
        IO::kwarn(exception);
    }

    void register_interrupt(InterruptService* interrupt_service){
        u32 idx = interrupt_service->interrupt_idx();
        u32 interrupt_flags = interrupt_service->interrupt_flags();
        u16 selector = (u16) (interrupt_flags >> 8);
        u8 flags = (u8)(interrupt_flags & 0xFF);
        CPU::add_entry(idx, (u32)interrupts_isrs[idx], 0x8, 0x8e);
        interrupts_v2[idx] = interrupt_service;
        #ifdef DEBUG_INTERRUPTS
        IO::dbg() << "registering interrupt = " << idx << "\n";
        #endif
    }

    void setup_interrupts(){
        register_interrupt(&trap_interrupt_service_0);
        register_interrupt(&trap_interrupt_service_1);
        register_interrupt(&trap_interrupt_service_2);
        register_interrupt(&trap_interrupt_service_3);
        register_interrupt(&trap_interrupt_service_4);
        register_interrupt(&trap_interrupt_service_5);
        register_interrupt(&trap_interrupt_service_6);
        register_interrupt(&trap_interrupt_service_7);
        register_interrupt(&trap_interrupt_service_8);
        register_interrupt(&trap_interrupt_service_9);
        register_interrupt(&trap_interrupt_service_10);
        register_interrupt(&trap_interrupt_service_11);
        register_interrupt(&trap_interrupt_service_12);
        register_interrupt(&trap_interrupt_service_13);
        register_interrupt(&trap_interrupt_service_14);
        register_interrupt(&trap_interrupt_service_15);
        register_interrupt(&trap_interrupt_service_16);
        register_interrupt(&trap_interrupt_service_17);
        register_interrupt(&trap_interrupt_service_18);
        register_interrupt(&trap_interrupt_service_19);
        register_interrupt(&trap_interrupt_service_20);
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

    void trap_handler(Registers registers){
        IO::kprint_str(exception_types[registers.int_no]);
        IO::kprintf("\n");
        CPU::end_of_interrupt(registers.int_no);
        return;
    }
}