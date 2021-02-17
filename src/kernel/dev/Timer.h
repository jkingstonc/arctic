#pragma once

#include "../Types.h"
#include "../arch/i386/cpu/I386CPU.h"
#include "../arch/i386/cpu/I386Interrupt.h"
#include "Device.h"
#include "../cpu/InterruptService.h"

namespace Device{
    class Timer : public Device, public CPU::InterruptService{
    public:
        void interrupt_handler(CPU::Registers registers) override;
        u32 interrupt_flags() override;
        u32 interrupt_idx() override;
    private:
        u32 m_tick = 0;
    };
}

namespace Dev::Timer{
    extern void init_timer(u32 frequency);
    extern void timer_handler(CPU::Registers registers);
}