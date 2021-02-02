#include "Keyboard.h"
#include "../io/Port.h"
#include "../KPrintf.h"

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
        IO::outb(0x21, 0xFD);
        IO::kprintf("[INFO] initialised keyboard\n");
    }
}