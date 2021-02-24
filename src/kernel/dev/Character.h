#pragma once

#include "Device.h"

namespace Device{
    class CharacterDevice : public Device {
    public:
        virtual void setup() override;
        CharacterDevice();
        ~CharacterDevice();
        virtual u8 read();
        virtual void write(u8 c);
        virtual String name() override;
        static const Type type = Type::CHARACTER;
    };
}