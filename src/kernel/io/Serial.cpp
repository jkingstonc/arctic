#include "Serial.h"

namespace IO{
    u1 setup_serial(){
        outb(COM1+1, 0x00); // disable interrupts
        outb(COM1+3, 0x80); // enable DLAB
        outb(COM1+0, 0x03); // set dividor to 3
        outb(COM1+1, 0x00);
        outb(COM1+3, 0x03); // 8 bits
        outb(COM1+2, 0xC7); // enable FIFO
        outb(COM1+4, 0x0B); // enable IRQs
        outb(COM1+4, 0x1E); // set loop-back mode
        outb(COM1+0, 0xAE); // test serial chip

        // if the serial chip isn't working then return false
        if(inb(COM1+0) != 0xAE){
            return false;
        }

        // set it to normal operation mode
        outb(COM1+4, 0x0F);
        return true;
    }

    u1 serial_received(u16 port){
        return inb(port+5) & 1;
    }

    char read_serial(u16 port){
        while(serial_received(port)==0);
        return inb(port);
    }

    u1 is_transmit_empty(u16 port){
        return inb(port+5) & 0x20;
    }

    void write_serial(u16 port, char c){
        while(is_transmit_empty(port)==0);
        outb(port, c);
    }
}