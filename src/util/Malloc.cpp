#include <util/Malloc.h>

#define KERNEL_INTERNAL
#ifdef KERNEL_INTERNAL
    #include <kernel/memory/KMalloc.h>
#endif

void* malloc(unsigned int size){
    #ifdef KERNEL_INTERNAL
        return (void*)Memory::kmalloc(size);
    #endif
    return 0;
}

void* realloc(void* data, unsigned int size){
    #ifdef KERNEL_INTERNAL
        return (void*)Memory::krealloc((unsigned int)data, size);
    #endif
    return 0;
}

void free(void* data){
    #ifdef KERNEL_INTERNAL
        Memory::kfree((unsigned int)data);
    #endif
}