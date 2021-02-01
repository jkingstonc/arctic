

#include "kernel/kprintf.h"



void welcome_msg(){
    kclear();
    kprintf("   #   \n");
    kprintf("  # #  \n");
    kprintf(" #   # \n");
    kprintf("#     #\n");
    kprintf("#######\n");
    kprintf("#     #\n");
    kprintf("#     #\n");
    kprintf("\n");
    kprintf("welcome to arctic OS\n");
}


// entry point for the kernel
int main(void){
    welcome_msg();
	return 0;
}