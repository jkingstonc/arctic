#pragma once

#include "../Types.h"

namespace Memory{

    extern void* kmalloc(size size);
    extern void kfree(void * data);

}