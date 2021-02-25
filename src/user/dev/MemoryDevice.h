#pragma once

#include <user/dev/Device.h>
#include <util/Types.h>

namespace Driver{
    /*
    A memory device is a device that 
    */
    class MemoryDevice : public Device{
    public:
        u32 physical_start(){
            return m_physical_start;
        }
        u32 size(){
            return m_size;
        }
    private:
        u32 m_physical_start;
        u32 m_size;
        // pointer to the virtual memory location that the memory buffer is mapped into
        // this is achieved via a system call
        u32* m_memory_buffer;
    }
}