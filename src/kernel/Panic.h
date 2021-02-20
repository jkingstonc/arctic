#pragma once

#include <kernel/Kernel.h>

#define PANIC(msg) Kernel::panic(__FILE__, __LINE__, msg)

namespace Kernel {
    u8 panic(const char* file, u32 line, const char* msg);
} 