// #pragma once

// #include "../Types.h"

// namespace CPU{
//     struct Registers {
//         u32 ds;
//         // Pushed by pusha.
//         u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
//         // pushed manually
//         u32 int_no, err_code;
//         // Pushed by the processor automatically.
//         u32 eip, cs, eflags, useresp, ss;
//     };
//     void setup_descriptor_tables();
//     void setup_protected_mode();
// }



#pragma once

namespace CPU{
    void setup_cpu();
}