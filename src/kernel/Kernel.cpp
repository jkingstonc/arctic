

#include "KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "cpu/CPU.h"
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
}


// entry point for the kernel
int main(void){
    IO::kclear();
    IO::kcolour(IO::KGreen);
    CPU::setup_cpu();
    for(;;);
    return 0;
}