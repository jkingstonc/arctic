#pragma once

#include "../Types.h"

namespace CPU{

    struct Registers {
        u32 ds;
        // Pushed by pusha.
        u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
        u32 int_no, err_code;
        // Pushed by the processor automatically.
        u32 eip, cs, eflags, useresp, ss;
    };
    extern void (*interrupts[256])(u32);
    extern const char* exception_types[20];
    extern void setup_interrupts();
    extern void register_interrupt(u32 idx, void(interrupt)(u32), u16 selector, u8 flags);
    extern void handle_exception(const char* exception);
    extern void end_of_interrupt(u32 idx);
    extern void set_irq_mask(u32 idx);
    extern void clear_irq_mask(u32 idx);
    extern void trap_handler(u32 idx);
}