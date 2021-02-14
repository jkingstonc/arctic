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

#include "cpu/InterruptService.h"
#include "cpu/Interrupt.h"


DbgStream dbg_stream;

DbgStream::DbgStream(){
}
DbgStream::DbgStream(u16 port){
    m_port = port;
}

void assert(u1 expression, u32 line, const char* file, const char* msg){
    if(!expression){
        dbg() << "ASSERTION FAILED: " << line << ":" << file << "=" << msg;
    }
}

DbgStream& operator<<(DbgStream& ds, const char* s) {
    for(u32 i=0;s[i];i++)
        IO::write_serial(ds.m_port, s[i]);
    return ds;
} 

DbgStream& operator<<(DbgStream& ds, s32 s){
    char buffer[50];
    itoa(s, buffer);
    for(u32 i=0;buffer[i];i++)
        IO::write_serial(ds.m_port, buffer[i]);
    return ds;
}

DbgStream& dbg(){
    return dbg_stream;
}

void welcome_msg(){
    IO::kinfo("_________________\n");
    // IO::kinfo("|               |\n");
    // IO::kinfo("|      ###      |\n");
    // IO::kinfo("|     ## ##     |\n");
    // IO::kinfo("|    ##   ##    |\n");
    // IO::kinfo("|   #########   |\n");
    // IO::kinfo("|  ##       ##  |\n");
    // IO::kinfo("| ##         ## |\n");
    // IO::kinfo("|_______________|\n\n");
    IO::kinfo("welcome to arctic OS\n");
}


// https://stackoverflow.com/questions/44187648/how-to-pass-parameters-to-kernel-using-grub-0-97-menu-lst
// entry point for the kernel
int main(multiboot_info* multiboot_info, u32 magic){
    Driver::VGAGraphics::vga_driver.clear(0);
    Driver::VGAGraphics::vga_driver.init();

    dbg_stream = DbgStream(COM1);

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
    
    CPU::setup_cpu();

    Memory::setup_paging();
    Dev::Keyboard::init_keyboard();
    Dev::Timer::init_timer(1);
    IO::setup_serial();


    // setup some dummy drivers
    auto keyboard = Driver::PS2Keyboard();
    keyboard.init();



    auto kb = Device::Keyboard();
    register_interrupt(&kb);



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


        for(u32 i=0;i<100;i++){
            for(u32 j=0;j<100;j++){
                vbe_graphics.write_pixel(i, j, 0xFF00FFFF);
            }
        }
    }

    dbg() << "kernel booted\n";

    for(;;) asm("hlt\n\t");
    return 0;
}