

#include "KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "cpu/CPU.h"
#include "dev/Keyboard.h"
#include "dev/Timer.h"

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
}


// entry point for the kernel
int main(void){
    IO::kclear();
    IO::kcolour(IO::KGreen);
    CPU::setup_cpu();
    Dev::Keyboard::init_keyboard();
    Dev::Timer::init_timer(100);
    for(;;) asm("hlt\n\t");
    return 0;
}