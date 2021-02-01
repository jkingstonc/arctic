

#include "KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "memory/GDT.h"
#include "interrupt/Interrupt.h"
#include "io/Port.h"


void welcome_msg(){

    IO::kprintf("   #   \n");
    IO::kprintf("  # #  \n");
    IO::kprintf(" #   # \n");
    IO::kprintf("#     #\n");
    IO::kprintf("#######\n");
    IO::kprintf("#     #\n");
    IO::kprintf("#     #\n");
    IO::kprintf("\n");
    IO::kprintf("welcome to arctic OS\n");

    auto shell = Shell::Shell::create();
    shell.run();
}


// entry point for the kernel
int main(void){

    IO::kclear();
    IO::kcolour(IO::KGreen);

    GDT::setup_gdt();
    Interrupt::setup_interrupts();

    //welcome_msg();

    asm volatile("int $0x3");
    
    for(;;){
        asm("hlt");
    }
	return 0;
}