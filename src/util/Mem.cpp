#include "Mem.h"


u0* memset(u0* dest, s32 ch, u32 count){
    for(u32 i=0;i<count;i++)
        *((u32*)dest + i)=ch;
    return dest;
}