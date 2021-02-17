#pragma once

#include "Device.h"

namespace Device{
    class CharacterDevice : public Device {
    public:
        CharacterDevice();
        ~CharacterDevice();
        virtual u8 read();
        virtual void write(u8 c);
        static const Type type = Type::CHARACTER;
    };
}