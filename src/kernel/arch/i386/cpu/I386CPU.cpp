#include "I386CPU.h"
#include "I386GDT.h"
#include "I386IDT.h"
#include "I386Interrupt.h"
#include "../../../io/KPrintf.h"
#include "../../../io/Debug.h"
#include "../../../Kernel.h"

extern "C" void setup_fpu();
extern "C" void enable_sse();
extern "C" void enter_protected();

namespace CPU{

    void setup_cpu_stage1(){

        // enable SSE (SIMD Streaming Extension)
        setup_fpu();
        enable_sse();
        setup_gdt();
        setup_interrupts();
    }
    void setup_cpu_stage2(){
        setup_idt();
        enter_protected();
        IO::dbg() << "setup i386 cpu\n";
    }
}