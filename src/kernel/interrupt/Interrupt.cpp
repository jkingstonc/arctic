#include "Interrupt.h"
#include "../KPrintf.h"

extern "C" void set_idt(Interrupt::IDT idt, u32 size);

namespace Interrupt{

    u8 setup_interrupts(){
        IDT idt = create_idt();
        install_idt(idt);
        return 1;
    }

    IDT create_idt(){
        return {};
    }

    void install_idt(IDT idt){
        //set_idt(idt, sizeof(idt));
    }
}