#pragma once

#include "../Types.h"
#include "../arch/i386/cpu/I386CPU.h"

namespace CPU{
    extern void regiser_interrupt(u32 idx, u32 flags, u32 handler);
    extern void register_interrupt(InterruptService* interrupt_service);
}