#include "Timer.h"
#include "../arch/i386/cpu/I386Interrupt.h"
#include "../arch/i386/cpu/I386IDT.h"
#include "../io/KPrintf.h"
#include "../io/Port.h"

#include <kernel/process/Scheduler.h>

namespace Device{

    void Timer::setup(){
        // The value we send to the PIT is the value to divide it's input clock
        // (1193180 Hz) by, to get our required frequency. Important to note is
        // that the divisor must be small enough to fit into 16-bits.
        u16 divisor = PITFrequency / m_target_freq;
        IO::outb(0x43, 0x36);

        // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
        u8 l = (u8)(divisor & 0xFF);
        u8 h = (u8)( (divisor>>8) & 0xFF );
        
        // Send the frequency divisor.
        IO::outb(0x40, l);
        IO::outb(0x40, h);
    }

    void Timer::interrupt_handler(CPU::Registers registers){
        m_tick++;

        auto count_per_second=read_count();
        // this has died
        // IO::dbg() << "tick: "<<(s32)m_tick<<"\n";
        u32 ticks_per_second = 1000;
        if(m_tick%ticks_per_second==0){
            //Process::scheduler.next_process();
            IO::dbg() << "second:)\n";
        }

        // if((m_tick*count_per_second) /PITFrequency >= 1){
        //     IO::dbg() << "second passed:)\n";
        //     m_tick=0; 
        // }
        CPU::end_of_interrupt(0x20);
    }

    u32 Timer::interrupt_flags(){
        return (0x08 << 8) | 0x8E;
    }
    
    u32 Timer::interrupt_idx(){
        return 0x20;
    }

    u32 Timer::tick() const {
        return m_tick;
    }

    u16 Timer::read_count(){
        u16 count = 0;
        asm volatile("cli");

        IO::outb(0x43, 0b00000000);
        count = IO::inb(0x40);
        count |= IO::inb(0x40)<<8;

        asm volatile("sti");
        return count;
    }
}


namespace Dev::Timer{

    u32 tick = 0;

    void timer_handler(CPU::Registers registers){
        tick++;
        CPU::end_of_interrupt(0x20);
    }

    void init_timer(u32 frequency){
        // CPU::register_interrupt(0x20, timer_handler, 0x08, 0x8E);

        // // The value we send to the PIT is the value to divide it's input clock
        // // (1193180 Hz) by, to get our required frequency. Important to note is
        // // that the divisor must be small enough to fit into 16-bits.
        // u16 divisor = 1193180 / frequency;
        // IO::outb(0x43, 0x36);

        // // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
        // u8 l = (u8)(divisor & 0xFF);
        // u8 h = (u8)( (divisor>>8) & 0xFF );

        // // Send the frequency divisor.
        // IO::outb(0x40, l);
        // IO::outb(0x40, h);
    }
}