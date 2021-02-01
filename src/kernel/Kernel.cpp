

#include "KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "interrupt/Interrupt.h"


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

    Memory::setup_gdt();
    Interrupt::setup_interrupts();

    welcome_msg();
    while(1){}
	return 0;
}