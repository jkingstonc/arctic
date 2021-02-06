

#include "io/KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "memory/Paging.h"
#include "cpu/CPU.h"
#include "dev/Keyboard.h"
#include "dev/Timer.h"
#include "Types.h"
#include "driver/PS2Keyboard.h"
#include "driver/VGAGraphics.h"
#include "utils/Optional.h"
#include "Multiboot.h"
#include "Panic.h"


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


// https://stackoverflow.com/questions/44187648/how-to-pass-parameters-to-kernel-using-grub-0-97-menu-lst
// entry point for the kernel
int main(multiboot_info* multiboot_info, u32 magic){
    IO::kclear();
    IO::kcolour(IO::VGACyan);
    if(multiboot_info->flags&1){
        IO::kinfo("multiboot info received!\n");
        IO::kinfo("memory (GB): ");
        // memory is in KB
        s32 mem = (multiboot_info->mem_lower)+(multiboot_info->mem_upper);
        f32 mem_f = (f32)mem/(f32)1000000;
        //IO::kprint_f(mem_f, 5);
        IO::kprint_c('\n');
        for(u32 i = 0;i<multiboot_info->mods_count; i++){
            multiboot_module_t* module = (multiboot_module_t*)multiboot_info->mods_addr;
            IO::kinfo("module cmd line: ");
            IO::kprint_int(module->cmdline);
            IO::kprint_c('\n');
        }
    }
    /// Memory::get_available_memory();
    CPU::setup_cpu();
    Dev::Keyboard::init_keyboard();
    Dev::Timer::init_timer(1);

    // setup some dummy drivers
    auto keyboard = Driver::PS2Keyboard();
    keyboard.init();
    auto graphics = Driver::VGAGraphics();
    graphics.init();
    graphics.colour(Driver::VGAGraphics::vga_green);
    // graphics.scroll(5);
    

    auto framebuffer = (u32*) multiboot_info->framebuffer_addr;

    IO::kinfo("framebuffer bbp: ");
    IO::kprint_int((u32)multiboot_info->framebuffer_bpp);
    IO::kprint_c('\n');

    IO::kinfo("framebuffer address: ");
    IO::kprint_int((u32)multiboot_info->framebuffer_addr);
    IO::kprint_c('\n');

    //for(int x =0;x<multiboot_info->framebuffer_width;x++)
    //    for(int y =0;x<multiboot_info->framebuffer_height;y++)
    //        framebuffer[y*multiboot_info->framebuffer_height + x]=0x992040;


    Kernel::panic("test panic!\n");

    
    Memory::setup_paging();

    // this should pagefault as paging is enabled
    //Memory::memset(0xfffffff0, '-', 5);


    for(;;) asm("hlt\n\t");
    return 0;
}