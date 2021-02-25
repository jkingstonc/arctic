#pragma once

#include <user/dev/Device.h>

namespace Driver{

    /*
    FrameBuffer driver

    https://www.kernel.org/doc/html/latest//fb/framebuffer.html
    */
    class FBDevice : public MemoryDevice{
    public:
        String name() override{
            return "fb";
        }
    private:
    };
}