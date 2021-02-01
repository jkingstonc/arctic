#pragma once

#include "../Types.h"



namespace Memory{




    // 8 bytes long
    struct GDTEntry{
        // the reason this is just a single type is because
        // the layout varies by architecture
        u64 descriptor;
    };

    struct GDT{
        GDTEntry entries[10];
    };

    extern GDT create_gdt();
    void install_gdt(GDT gdt);
    extern GDT& add_entry(GDT& gdt, u32 idx, u32 base, u32 limit, u16 flag);

}