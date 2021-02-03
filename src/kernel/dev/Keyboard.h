#pragma once

#include "../Types.h"

namespace Dev{
    namespace Keyboard{
        extern const u8 keyboard_map[128];
        extern void init_keyboard();
        extern void keyboard_handler(u32 idx);
    }
}