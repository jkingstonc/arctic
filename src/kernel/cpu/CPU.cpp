#include "CPU.h"
#include "GDT.h"
#include "IDT.h"
#include "Interrupt.h"
#include "../io/KPrintf.h"

extern "C" void enter_protected();

namespace CPU{
    void setup_cpu(){
        setup_gdt();
        IO::kinfo("GDT initialised\n");
        enter_protected();
        IO::kinfo("Entered 32-bit protected mode\n");
        setup_interrupts();
        IO::kinfo("IDT initialised\n");
    }
}