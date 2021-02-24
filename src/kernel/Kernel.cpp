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
#include <kernel/memory/Heap.h>
#include <kernel/memory/KMalloc.h>
#include <kernel/process/Process.h>



void assert(u1 expression, u32 line, const char* file, const char* msg){
    if(!expression){
        IO::dbg() << "ASSERTION FAILED: " << line << ":" << file << "=" << msg;
    }
}

// https://stackoverflow.com/questions/44187648/how-to-pass-parameters-to-kernel-using-grub-0-97-menu-lst
// entry point for the kernel
int main(multiboot_info* multiboot_info, u32 magic){
    IO::dbg_stream = IO::DbgStream(COM1);
    
    Memory::setup_kernel_heap();
    IO::setup_serial();
    
    CPU::setup_cpu_stage1();


    Device::setup_devices();
 
    auto tm = Device::Timer();
    auto kb = Device::Keyboard();
    CPU::register_interrupt(&kb);
    CPU::register_interrupt(&tm);


    CPU::setup_cpu_stage2();


    //Memory::setup_paging();


    
    Ref<s32> ref((s32*)Memory::kmalloc(sizeof(s32)));
    Ref<s32> other_ref = ref;
    *other_ref=123;
    IO::dbg() << "ref counter: "<<other_ref.count()<<"\n";

    Ref<Process::Process> proc = Process::Process::create_kernel_proc();


    // // the issue is that that the vbe memory map is not mapped into the virtual address space
    Driver::VGAGraphics::vga_driver.colour(Driver::VGAGraphics::vga_red);


    {
        auto vbe_graphics = Driver::VBEGraphics(
            (u32*)multiboot_info->framebuffer_addr,
            (u32)multiboot_info->framebuffer_width,
            (u32)multiboot_info->framebuffer_height,
            (u8)multiboot_info->framebuffer_bpp
        );
        vbe_graphics.init();
        vbe_graphics.clear(0xFF);
        for(u32 i=0;i<vbe_graphics.width();i++){
            for(u32 j=0;j<vbe_graphics.height();j++){
                vbe_graphics.write_pixel(i, j, 0x00FFFF);
            }
        }


        // IO::dbg() << "sqrt(4)="<<sqrt(4)<<"\n";
        // #define RAD 50
        // for(u32 i=vbe_graphics.width()/2 -50;i<vbe_graphics.width()/2+50;i++){
        //     for(u32 j=vbe_graphics.height()/2 -50;j<vbe_graphics.height()/2+50;j++){
        //         if(sqrt(
        //             pow((int)(i-vbe_graphics.width()/2),2)
        //             +
        //             pow((int)(j-vbe_graphics.height()/2),2)
        //             )<RAD){
        //             vbe_graphics.write_pixel(j,i,0x00FF00);
        //         }
        //     }
        // }

    }

    // struct {
    //     FS::InitRDHeader header;
    //     FS::InitRDEntry entry1;
    // } rd;

    // rd.header.magic = 0x123;
    // rd.header.n_files = 1;
    // rd.entry1.filename="hello world!";

    // FS::setup_initrd((u32)&rd);

    IO::dbg() << "kernel booted version " << VERSION << "\n";

    for(;;) asm("hlt\n\t");
    return 0;
}