#pragma once

#include "Device.h"

namespace Device{
    class MemoryDevice : public Device {
    public:
        MemoryDevice();
        ~MemoryDevice();
        static const Type type = Type::MEMORY;
    };
}