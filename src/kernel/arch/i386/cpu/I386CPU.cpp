#include "I386CPU.h"
#include "I386GDT.h"
#include "I386IDT.h"
#include "I386Interrupt.h"
#include "../../../io/KPrintf.h"
#include "../../../io/Debug.h"
#include "../../../Kernel.h"

extern "C" void enter_protected();

namespace CPU{
    void setup_cpu(){
        setup_gdt();
        setup_idt();
        setup_interrupts();
        enter_protected();
        IO::dbg() << "setup i386 cpu\n";
    }
}