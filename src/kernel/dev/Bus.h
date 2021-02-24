#pragma once

#include <kernel/dev/Device.h>

namespace Device{
    class Bus : public Device{
    public:
        Bus();
        ~Bus();
        String name() override;
    private:
    };
}