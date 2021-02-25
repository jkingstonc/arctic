#pragma once

#include <util/Types.h>
#include <util/String.h>

namespace Driver{


    class Driver{
    public:
        // name of the driver
        // this is mapped to /driver/d0....dn
        virtual String name() = 0;

        // registers a driver with the kernel and mounts it into /driver/
        static u1 register_driver(Driver* driver){
            return true;
        }

    private:
    };

}