

#include "io/KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "memory/Paging.h"
#include "cpu/CPU.h"
#include "dev/Keyboard.h"
#include "dev/Timer.h"
#include "multiboot.h"
#include "Types.h"
#include "driver/PS2Keyboard.h"
#include "driver/VGAGraphics.h"
#include "utils/Optional.h"

void welcome_msg(){
    IO::kinfo("   #   \n");
    IO::kinfo("  # #  \n");
    IO::kinfo(" #   # \n");
    IO::kinfo("#     #\n");
    IO::kinfo("#######\n");
    IO::kinfo("#     #\n");
    IO::kinfo("#     #\n");
    IO::kinfo("\n");
    IO::kinfo("welcome to arctic OS\n");
}


// entry point for the kernel
int main(u32* multiboot_info_addr, u32 magic){
    IO::kclear();
    IO::kcolour(IO::VGACyan);

    multiboot_info_t* multiboot_info = (multiboot_info_t*) multiboot_info_addr;
    if(multiboot_info->flags&1==0){
        IO::kwarn("invalid magic, multi-boot not supported\n");
    }else{
        IO::kinfo("boot dev: ");
        IO::kprint_int(multiboot_info->boot_device);
        IO::kprint_c('\n');
        IO::kinfo("available memory (kb): ");
        IO::kprint_int(multiboot_info->mem_upper);
        IO::kprint_c('\n');
    }

    /// Memory::get_available_memory();
    CPU::setup_cpu();
    Dev::Keyboard::init_keyboard();
    Dev::Timer::init_timer(1);
    Memory::setup_paging();

    // setup some dummy drivers
    auto keyboard = Driver::PS2Keyboard();
    keyboard.init();
    auto graphics = Driver::VGAGraphics();
    graphics.init();
    graphics.colour(Driver::VGAGraphics::vga_green);
    // graphics.scroll(5);

    

    for(;;) asm("hlt\n\t");
    return 0;
}