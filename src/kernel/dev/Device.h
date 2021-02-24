#pragma once

#include <kernel/Kernel.h>
#include <util/String.h>
#include <util/Vector.h>

namespace Device{


    enum class Type : u8{
        VOID,
        CHARACTER,
        BLOCK
    };

    class Device{
    public:
        Device();
        ~Device();
        virtual void setup();
        virtual String name();
        virtual u32 id();
        static const Type type;
    };


    class DeviceTree{
    public:
        Device* get(u32 id);
        void setup_dev_tree();
    private:
        Vector<Device*> m_devices;
    };

    extern void setup_devices();
    extern DeviceTree* kernel_dev_tree;
}   