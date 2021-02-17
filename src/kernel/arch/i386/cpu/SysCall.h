#pragma once

#include "../../../io/Types.h"

namespace CPU{
    extern void register_syscall(u32 flags, u32 handler);
}