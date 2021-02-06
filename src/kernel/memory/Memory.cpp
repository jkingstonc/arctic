#include "Memory.h"
#include "../io/KPrintf.h"
#include "../Types.h"


extern "C" void detect_memory(u32 structure);

namespace Memory{

    u32 get_available_memory(){
        u32 mem_map[10];
        detect_memory((u32)&mem_map);
        return 0;
    }

    void memset(u32 ptr, u32 value, size size){
        for(u32 i=0;i<size;i++)
           *((u32*)(ptr+i))=value;
    }
}