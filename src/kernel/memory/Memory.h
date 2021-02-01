#pragma once

#include "../Types.h"

namespace Memory {

    class EFIMemoryMap{};

    class EFIMemoryDescriptor{};

    // get the amount of available amount of memory the system has
    extern u64 get_memory_size(EFIMemoryMap* mem_map, u64 mem_map_entries, u64 mem_map_desc_size);
}