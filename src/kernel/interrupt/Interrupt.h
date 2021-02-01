#pragma once

#include "../Types.h"

namespace Interrupt{

    // Interrupt Descriptor Table
    struct IDT{};


    extern u8 setup_interrupts();
    extern IDT create_idt();
    void install_idt(IDT idt);

}