
#pragma once

#include "Driver.h"
#include "../dev/Keyboard.h"
#include "../Types.h"

namespace Driver{
    class PS2Keyboard : public Driver {
        public:
        PS2Keyboard();
        ~PS2Keyboard();
        void init() override;
        void close() override;
        u32 read();
        private:
        Device::Keyboard m_keyboard_device;
        u32 m_key;
    };
    void ps2_keyboard_interrupt_handler(u32 idx);
}