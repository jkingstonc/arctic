#pragma once

#include "../Kernel.h"

namespace CPU{
    class InterruptService {
    public:
        virtual void interrupt_handler(CPU::Registers registers){}
        virtual u32 interrupt_idx(){return -1;}
        virtual u32 interrupt_flags(){return -1;}
    };
}