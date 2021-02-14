#pragma once

#include "../Types.h"
#include "../arch/i386/cpu/I386CPU.h"
#include "../arch/i386/cpu/I386Interrupt.h"

namespace Dev::Timer{
    extern void init_timer(u32 frequency);
    extern void timer_handler(CPU::Registers registers);
}