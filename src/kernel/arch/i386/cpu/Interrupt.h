#pragma once

#include "../../../Types.h"
#include "CPU.h"

namespace CPU{
    extern void (*interrupts[256])(Registers);
    extern const char* exception_types[31];
    extern void setup_interrupts();
    extern void register_interrupt(u32 idx, void(interrupt)(Registers), u16 selector, u8 flags);
    extern void handle_exception(const char* exception);
    extern void end_of_interrupt(u32 idx);
    extern void set_irq_mask(u32 idx);
    extern void clear_irq_mask(u32 idx);
    extern void trap_handler(Registers registers);
}