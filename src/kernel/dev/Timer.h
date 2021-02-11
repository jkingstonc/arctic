#pragma once

#include "../Types.h"
#include "../arch/i386/cpu/CPU.h"
#include "../arch/i386/cpu/Interrupt.h"

namespace Dev::Timer{
    extern void init_timer(u32 frequency);
    extern void timer_handler(CPU::Registers registers);
}