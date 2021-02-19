#include <kernel/Kernel.h>
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
#include "util/Optional.h"
#include "util/Math.h"
#include "Multiboot.h"
#include "Panic.h"
#include <util/String.h>
#include "io/Serial.h"
#include <util/SStream.h>
#include <util/Numeric.h>

#include "io/Debug.h"
#include "cpu/InterruptService.h"
#include "cpu/Interrupt.h"
#include <kernel/fs/vfs.h>
#include <kernel/fs/Initrd.h>
#include <util/OrderedVector.h>


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
    
    CPU::setup_cpu_stage1();
    auto kb = Device::Keyboard();
    auto tm = Device::Timer();
    register_interrupt(&kb);
    register_interrupt(&tm);


    CPU::setup_cpu_stage2();

    Memory::setup_paging();
    IO::setup_serial();

    // // the issue is that that the vbe memory map is not mapped into the virtual address space
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
    //     for(u32 i=0;i<vbe_graphics.width();i++){
    //         for(u32 j=0;j<vbe_graphics.height();j++){
    //             vbe_graphics.write_pixel(i, j, 0xABCDEFFF);
    //         }
    //     }
    // }

    struct {
        FS::InitRDHeader header;
        FS::InitRDEntry entry1;
    } rd;

    rd.header.magic = 0x123;
    rd.header.n_files = 1;
    rd.entry1.filename="hello world!";

    FS::setup_initrd((u32)&rd);

    IO::dbg() << "kernel booted version " << VERSION << "\n";

    for(;;) asm("hlt\n\t");
    return 0;
}