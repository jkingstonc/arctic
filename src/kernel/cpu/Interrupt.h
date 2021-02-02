#pragma once

#include "../Types.h"

namespace CPU{

    extern const char* exception_types[20];
    extern void handle_exception(const char* exception);
    extern void end_of_interrupt(u32 idx);
    extern void set_irq_mask(u32 idx);
    extern void clear_irq_mask(u32 idx);
}

extern "C" void exec_0_isr();
extern "C" void exec_1_isr();
extern "C" void exec_2_isr();
extern "C" void exec_3_isr();
extern "C" void exec_4_isr();
extern "C" void exec_5_isr();
extern "C" void exec_6_isr();
extern "C" void exec_7_isr();
extern "C" void exec_8_isr();
extern "C" void exec_9_isr();
extern "C" void exec_10_isr();
extern "C" void exec_11_isr();
extern "C" void exec_12_isr();
extern "C" void exec_13_isr();
extern "C" void exec_14_isr();
extern "C" void exec_15_isr();
extern "C" void exec_16_isr();
extern "C" void exec_17_isr();
extern "C" void exec_18_isr();
extern "C" void exec_19_isr();
extern "C" void exec_20_isr();
extern "C" void exec_keyboard_isr();