#pragma once

#include "Driver.h"
#include "../Types.h"

namespace Driver{

    class VBEGraphics : public Driver {
    public:
        VBEGraphics();
        VBEGraphics(u32* framebuffer, u32 width, u32 height, u8 pixel_depth);
        ~VBEGraphics();
        void init() override;
        void close() override;
        void write_pixel(u32 x, u32 y, u32 value);
        u32 read_pixel(u32 x, u32 y);
    private:
        u32* m_framebuffer;
        u32  m_width;
        u32  m_height;
        u8  m_pixel_depth;
    };

}