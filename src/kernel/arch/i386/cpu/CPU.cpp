#include "CPU.h"
#include "GDT.h"
#include "IDT.h"
#include "Interrupt.h"
#include "../../../io/KPrintf.h"
#include "../../../Kernel.h"

extern "C" void enter_protected();

namespace CPU{
    void setup_cpu(){
        setup_gdt();
        setup_idt();
        setup_interrupts();
        enter_protected();
        dbg() << "setup i386 cpu\n";
    }
}