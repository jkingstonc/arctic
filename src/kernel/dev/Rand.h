#pragma once

#include <kernel/dev/Character.h>
#include <util/String.h>

namespace Device{
    class Rand : public CharacterDevice {
    public:
        u8 read() override;
        void write(u8 c) override;
        String name() override;
    private:
        u8 m_seed;
    };
}