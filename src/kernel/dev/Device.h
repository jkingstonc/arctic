#pragma once

#include "../Types.h"

namespace Device{
    enum class Type : u8{
        CHARACTER,
        BLOCK
    };

    class Device{
    public:
        Device();
        ~Device();
        static const Type type;
    };
}