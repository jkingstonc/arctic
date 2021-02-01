#include "Port.h"


namespace IO{

        // send a byte out a port
    void outb(u16 port, u8 val){
        asm volatile("outb %1, %0" : : "dN"(port), "a"(val));
    }
    // read a byte in from a port
    u8 inb(u16 port){
        u8 return_val;
        asm volatile("inb %1, %0" : "=a"(return_val) : "dN"(port));
        return return_val;
    }

    u16 inw(u16 port){
        u16 return_val;
        asm volatile("inw %1, %0" : "=a"(return_val) : "dN"(port));
        return return_val;
    }
}