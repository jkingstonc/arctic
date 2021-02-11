// #include "CPU.h"
// #include "GDT.h"
// #include "IDT.h"
// #include "Interrupt.h"
// #include "../io/KPrintf.h"

// extern "C" void enter_protected();

// namespace CPU{
//     void setup_descriptor_tables(){
//         setup_gdt();
//         IO::kinfo("GDT initialised\n");
//         setup_interrupts();
//         IO::kinfo("IDT initialised\n");
//     }

//     void setup_protected_mode(){
//         enter_protected();
//         IO::kinfo("entered 32-bit protected mode\n");
//     }
// }