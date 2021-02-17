#pragma once

#include "../Types.h"

namespace IO{
    // send a byte out a port
    extern void outb(u16 port, u8 val);
    // read a byte in from a port
    extern u8 inb(u16 port);
    extern u16 inw(u16 port);
}