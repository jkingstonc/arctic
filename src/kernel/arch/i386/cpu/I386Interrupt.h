#pragma once

#include "../../../Types.h"
#include "I386CPU.h"
#include "../../../cpu/InterruptService.h"
#include "../../../io/Debug.h"

namespace CPU{
    extern void (*interrupts[256])(Registers);
    extern InterruptService* interrupts_v2[256];
    
    extern const char* exception_types[31];
    extern void setup_interrupts();
    extern void register_interrupt(u32 idx, void(interrupt)(Registers), u16 selector, u8 flags);
    extern void handle_exception(const char* exception);
    extern void end_of_interrupt(u32 idx);
    extern void set_irq_mask(u32 idx);
    extern void clear_irq_mask(u32 idx);
    extern void trap_handler(Registers registers);

// const char* exception_types[31] = {
//         "Division By Zero",
//         "Debug",
//         "Non Maskable Interrupt",
//         "Breakpoint",
//         "Arithmetic Overflow",
//         "Bound Range Exceeded",
//         "Invalid Opcode",
//         "Device Not Available",
//         "Double Fault",
//         "Coprosessor Segment Overrun",
//         "Invalid TSS",
//         "Segment Not Present",
//         "Stack-Segment Fault",
//         "General Protection Fault",
//         "Page Fault",
//         "Reserved",
//         "x87 Floating Point Exception",
//         "Alignment Check",
//         "Machine Check",
//         "SIMD Floating Point Exception",
//         "Virtualisation Exception",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Reserved",
//         "Triple Fault"
//     };

    class TrapInterruptService0 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = division by zero\n"; CPU::end_of_interrupt(0x0);};
        virtual u32 interrupt_idx() override {return 0;};
    };
    class TrapInterruptService1 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = debug\n"; CPU::end_of_interrupt(0x1);};
        virtual u32 interrupt_idx() override {return 1;};
    };
    class TrapInterruptService2 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = non maskable interrupt\n"; CPU::end_of_interrupt(0x2);};
        virtual u32 interrupt_idx() override {return 2;};
    };
    class TrapInterruptService3 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = breakpoint\n"; CPU::end_of_interrupt(0x3);};
        virtual u32 interrupt_idx() override {return 3;};
    };
    class TrapInterruptService4 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = non maskable interrupt\n"; CPU::end_of_interrupt(0x4);};
        virtual u32 interrupt_idx() override {return 4;};
    };
    class TrapInterruptService5 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = bound range exceeded\n"; CPU::end_of_interrupt(0x5);};
        virtual u32 interrupt_idx() override {return 5;};
    };
    class TrapInterruptService6 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = invalid opcode\n"; CPU::end_of_interrupt(0x6);};
        virtual u32 interrupt_idx() override {return 6;};
    };
    class TrapInterruptService7 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = device not available\n"; CPU::end_of_interrupt(0x7);};
        virtual u32 interrupt_idx() override {return 7;};
    };
        class TrapInterruptService8 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = double fault\n"; CPU::end_of_interrupt(0x8);};
        virtual u32 interrupt_idx() override {return 8;};
    };
    class TrapInterruptService9 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = crossprocessor segment overrun\n"; CPU::end_of_interrupt(0x9);};
        virtual u32 interrupt_idx() override {return 9;};
    };
    class TrapInterruptService10 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = invalid tss\n"; CPU::end_of_interrupt(0xA);};
        virtual u32 interrupt_idx() override {return 0xA;};
    };
    class TrapInterruptService11 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = segment not present\n"; CPU::end_of_interrupt(0xB);};
        virtual u32 interrupt_idx() override {return 0xA;};
    };
    class TrapInterruptService12 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = stack segment fault\n"; CPU::end_of_interrupt(0xC);};
        virtual u32 interrupt_idx() override {return 0xC;};
    };
    class TrapInterruptService13 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = general protection fault\n"; CPU::end_of_interrupt(0xD);};
        virtual u32 interrupt_idx() override {return 0xD;};
    };
    class TrapInterruptService14 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = page fault\n"; CPU::end_of_interrupt(0xE);};
        virtual u32 interrupt_idx() override {return 0xE;};
    };
    class TrapInterruptService15 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0xF);};
        virtual u32 interrupt_idx() override {return 0xF;};
    };
    class TrapInterruptService16 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = floating point exception\n"; CPU::end_of_interrupt(0x10);};
        virtual u32 interrupt_idx() override {return 0x10;};
    };
    class TrapInterruptService17 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = alignment check\n"; CPU::end_of_interrupt(0x11);};
        virtual u32 interrupt_idx() override {return 0x11;};
    };
    class TrapInterruptService18 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = machine check\n"; CPU::end_of_interrupt(0x12);};
        virtual u32 interrupt_idx() override {return 0x12;};
    };
    class TrapInterruptService19 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = simd floating point exception\n"; CPU::end_of_interrupt(0x13);};
        virtual u32 interrupt_idx() override {return 0x13;};
    };
    class TrapInterruptService20 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = virtualisation exception\n"; CPU::end_of_interrupt(0x14);};
        virtual u32 interrupt_idx() override {return 0x14;};
    };



    class TrapInterruptService21 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x15);};
        virtual u32 interrupt_idx() override {return 0x15;};
    };
    class TrapInterruptService22 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x16);};
        virtual u32 interrupt_idx() override {return 0x16;};
    };
    class TrapInterruptService23 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x17);};
        virtual u32 interrupt_idx() override {return 0x17;};
    };
    class TrapInterruptService24 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x18);};
        virtual u32 interrupt_idx() override {return 0x18;};
    };
    class TrapInterruptService25 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x19);};
        virtual u32 interrupt_idx() override {return 0x19;};
    };
    class TrapInterruptService26 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x1A);};
        virtual u32 interrupt_idx() override {return 0x1A;};
    };
    class TrapInterruptService27 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x1B);};
        virtual u32 interrupt_idx() override {return 0x1B;};
    };
    class TrapInterruptService28 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x1C);};
        virtual u32 interrupt_idx() override {return 0x1C;};
    };
    class TrapInterruptService29 : public InterruptService{
    public:
        virtual void interrupt_handler(CPU::Registers registers) override {IO::dbg() << "TRAP = reserved\n"; CPU::end_of_interrupt(0x1D);};
        virtual u32 interrupt_idx() override {return 0x1D;};
    };
}