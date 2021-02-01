

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

    Memory::setup_gdt();
    Interrupt::setup_interrupts();
    u16 cursor_location = 5 * 80 + 5;
    IO::outb(0x3D4, 14);
    IO::outb(0x3D5, cursor_location >> 8);
    IO::outb(0x3D4, 14);
    IO::outb(0x3D5, cursor_location);
    welcome_msg();
    while(1){}
	return 0;
}