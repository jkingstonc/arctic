#pragma once

#include "../Types.h"
#include "../cpu/CPU.h"
#include "../cpu/Interrupt.h"
#include "Character.h"

namespace Device{
    class Keyboard : public CharacterDevice{
        public:
        u8 read() override;
        void write(u8 c) override;
    };
}

namespace Dev{
    namespace Keyboard{
        extern const u8 keyboard_map[128];
        extern void init_keyboard();
        extern void keyboard_handler(CPU::Registers registers);
    }
}