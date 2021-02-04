#pragma once

#include "Device.h"

namespace Device{
    class BlockDevice : public Device {
    public:
        BlockDevice();
        ~BlockDevice();
        static const Type type = Type::BLOCK;
    };
}