#pragma once

#include "../Types.h"

namespace CPU{
    extern void regiser_interrupt(u32 idx, u32 flags, u32 handler);
}