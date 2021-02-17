#pragma once

#include "Port.h"

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

namespace IO{
    extern u1 setup_serial();
    extern u1 serial_received(u16 port);
    extern char read_serial(u16 port);
    extern void write_serial(u16 port, char c);
    extern u1 is_transmit_empty(u16 port);
}