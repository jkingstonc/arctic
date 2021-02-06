#include "VBEGraphics.h"

namespace Driver{
    VBEGraphics::VBEGraphics(){}
    VBEGraphics::VBEGraphics(u32* framebuffer, u32 width, u32 height, u8 pixel_depth)
        : m_framebuffer(framebuffer), m_width(width), m_height(height), m_pixel_depth(pixel_depth)
    {}
    VBEGraphics::~VBEGraphics(){}
    void VBEGraphics::init(){}
    void VBEGraphics::close(){}
    void VBEGraphics::write_pixel(u32 x, u32 y, u32 value){
        m_framebuffer[x + y*m_width] = value;
    }
    u32 VBEGraphics::read_pixel(u32 x, u32 y){
        return m_framebuffer[x + y*m_width];
    }
}