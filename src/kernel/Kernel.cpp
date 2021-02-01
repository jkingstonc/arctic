

#include "KPrintf.h"
#include "shell/Shell.h"


void welcome_msg(){
    IO::kclear();
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
    welcome_msg();
	return 0;
}