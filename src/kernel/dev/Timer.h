#pragma once

#include "../Types.h"
#include "../arch/i386/cpu/I386CPU.h"
#include "../arch/i386/cpu/I386Interrupt.h"
#include "Device.h"
#include "../cpu/InterruptService.h"

namespace Device{
    class Timer : public Device, public CPU::InterruptService{
    public:
        void setup() override;
        void interrupt_handler(CPU::Registers registers) override;
        u32 interrupt_flags() override;
        u32 interrupt_idx() override;
        u32 tick() const;
        u16 read_count();
    private:
        u32 m_tick = 1;
        u32 m_target_freq = 1193180/100;
        u32 m_frequency;
        static const u32 PITFrequency = 1193180;
    };
}

namespace Dev::Timer{
    extern void init_timer(u32 frequency);
    extern void timer_handler(CPU::Registers registers);
}