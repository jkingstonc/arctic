#pragma once

#include <util/String.h>

namespace Driver{
    class Device{
    public:
        // the name of the device will be mounted on /dev/name
        virtual String name() = 0;
    private:
    };
}