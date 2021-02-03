

#include "io/KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "memory/Paging.h"
#include "cpu/CPU.h"
#include "dev/Keyboard.h"
#include "dev/Timer.h"
#include "multiboot.h"

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
int main(multiboot_info_t* multiboot_info, u32 magic){
    IO::kclear();
    IO::kcolour(IO::KGreen);
    CPU::setup_cpu();
    Dev::Keyboard::init_keyboard();
    Dev::Timer::init_timer(1);
    Memory::setup_paging();
    // if bit 1 is set then we have available memory
    if(multiboot_info->flags & 1){
        IO::kprintf("[INFO] available memory (kb): ");
        u32 lower = multiboot_info->mem_lower;
        u32 upper = multiboot_info->mem_upper;
        IO::kprint_int(lower);
    }
    for(;;) asm("hlt\n\t");
    return 0;
}