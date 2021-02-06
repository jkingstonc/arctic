#pragma once

#include "Types.h"

namespace Kernel {
    u8 panic(const char* file, u32 line, const char* msg);
} 