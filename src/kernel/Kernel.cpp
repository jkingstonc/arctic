#include "Kernel.h"
#include "cpu/CPU.h"
#include "io/KPrintf.h"
#include "shell/Shell.h"
#include "memory/Memory.h"
#include "memory/Paging.h"
#include "dev/Keyboard.h"
#include "dev/Timer.h"
#include "Types.h"
#include "driver/PS2Keyboard.h"
#include "driver/VGAGraphics.h"
#include "driver/VBEGraphics.h"
#include "utils/Optional.h"
#include "utils/Math.h"
#include "Multiboot.h"
#include "Panic.h"
#include "utils/string.h"
#include "io/Serial.h"
#include "utils/SStream.h"
#include "utils/Numeric.h"

#include "io/Debug.h"
#include "cpu/InterruptService.h"
#include "cpu/Interrupt.h"


void assert(u1 expression, u32 line, const char* file, const char* msg){
    if(!expression){
        IO::dbg() << "ASSERTION FAILED: " << line << ":" << file << "=" << msg;
    }
}

// https://stackoverflow.com/questions/44187648/how-to-pass-parameters-to-kernel-using-grub-0-97-menu-lst
// entry point for the kernel
int main(multiboot_info* multiboot_info, u32 magic){
    IO::dbg_stream = IO::DbgStream(COM1);
    Driver::VGAGraphics::vga_driver.clear(0);
    Driver::VGAGraphics::vga_driver.init();
    
    CPU::setup_cpu();
    Dev::Keyboard::init_keyboard();
    Dev::Timer::init_timer(1);
    Memory::setup_paging();
    IO::setup_serial();

    auto kb = Device::Keyboard();
    auto tm = Device::Timer();
    register_interrupt(&kb);


    // Driver::VGAGraphics::vga_driver.colour(Driver::VGAGraphics::vga_red);
    // {
    //     auto vbe_graphics = Driver::VBEGraphics(
    //         (u32*)multiboot_info->framebuffer_addr,
    //         (u32)multiboot_info->framebuffer_width,
    //         (u32)multiboot_info->framebuffer_height,
    //         (u8)multiboot_info->framebuffer_bpp
    //     );
    //     vbe_graphics.init();
    //     vbe_graphics.clear(0xFF);


    //     for(u32 i=0;i<100;i++){
    //         for(u32 j=0;j<100;j++){
    //             vbe_graphics.write_pixel(i, j, 0xFF00FFFF);
    //         }
    //     }
    // }

    IO::dbg() << "kernel booted version " << VERSION << "\n";

    for(;;) asm("hlt\n\t");
    return 0;
}