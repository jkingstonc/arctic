#include "PS2Keyboard.h"
#include "../io/KPrintf.h"
#include "../cpu/Interrupt.h"
#include "../dev/Keyboard.h"
#include "../io/Port.h"

namespace Driver{
    PS2Keyboard::PS2Keyboard(){}
    PS2Keyboard::~PS2Keyboard(){}

    void PS2Keyboard::init(){
        IO::kinfo("initialising PS2Keyboard driver\n");
    }

    void PS2Keyboard::close(){

    }

    u32 PS2Keyboard::read(){
        return 0;
    }
}