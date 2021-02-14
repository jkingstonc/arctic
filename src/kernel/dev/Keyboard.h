#pragma once

#include "../Types.h"
#include "../arch/i386/cpu/I386CPU.h"
#include "../arch/i386/cpu/I386Interrupt.h"
#include "Character.h"
#include "../cpu/InterruptService.h"

namespace Device{
    class Keyboard : public CharacterDevice, public CPU::InterruptService {
        public:
        u8 read() override;
        void write(u8 c) override;
        virtual void interrupt_handler(CPU::Registers registers) override;
        virtual u32 interrupt_idx() override;
        virtual u32 interrupt_flags() override;
    };
}

namespace Dev{
    namespace Keyboard{
        extern const u8 keyboard_map[128];
        extern void init_keyboard();
        extern void keyboard_handler(CPU::Registers registers);
    }
}