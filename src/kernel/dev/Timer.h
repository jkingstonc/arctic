#pragma once

#include "../Types.h"
#include "../cpu/CPU.h"
#include "../cpu/Interrupt.h"

namespace Dev::Timer{
    extern void init_timer(u32 frequency);
    extern void timer_handler(CPU::Registers registers);
}