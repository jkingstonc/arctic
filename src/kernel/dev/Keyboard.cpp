#include "Keyboard.h"
#include "../io/Port.h"
#include "../KPrintf.h"
#include "../cpu/IDT.h"
#include "../cpu/Interrupt.h"

namespace Dev::Keyboard{

    const u8 keyboard_map[128] = {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',
        '9', '0', '-', '=', '\0',
        '\t',
        'q', 'w', 'e', 'r',
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
        0,
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
        '\'', '`', 0,
        '\\', 'z', 'x', 'c', 'v', 'b', 'n',
        'm', ',', '.', '/', 0,
        '*',
        0,
        ' ',
        0,
        0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0,
        0,
        0,
        '-',
        0,
        0,
        0,
        '+',
        0,
        0,
        0,
        0,
        0,
        0, 0, 0,
        0,
        0,
        0
    };

    void init_keyboard(){
        // to enable only the keyboard:
        IO::outb(0x21, 0xFD);
        IO::kprintf("[INFO] initialised keyboard\n");
        // start at 0x20 as previous traps were remapped to start at 0-19
        CPU::register_interrupt(0x21, keyboard_handler, 0x08, 0x8E);
    }

    
    void keyboard_handler(u32 idx){
        // KEYBOARD IN PORT     = 0X60
        // KEYBOARD STATUS PORT = 0x64
        // read from the keyboard in port
        const u8 status = IO::inb(0x64);
        const u8 scancode = IO::inb(0x60);
        /* Lowest bit of status will be set if buffer is not empty */
        if (status & 0x01) {
            if(scancode > 0)
                IO::kprint_c(Dev::Keyboard::keyboard_map[scancode]);
        }
        CPU::end_of_interrupt(0x21);
        return;
    }
}