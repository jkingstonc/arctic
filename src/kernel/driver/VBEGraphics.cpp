#include "VBEGraphics.h"

namespace Driver{
    VBEGraphics::VBEGraphics(){}
    VBEGraphics::VBEGraphics(u32* framebuffer, u32 width, u32 height, u8 pixel_depth)
        : m_framebuffer(framebuffer), m_width(width), m_height(height), m_pixel_depth(pixel_depth)
    {}
    VBEGraphics::~VBEGraphics(){}
    void VBEGraphics::init(){}
    void VBEGraphics::close(){}
    u32 VBEGraphics::width(){
        return m_width;
    }
    u32 VBEGraphics::height(){
        return m_height;
    }
    u32 VBEGraphics::pixel_depth(){
        return m_pixel_depth;
    }
    void VBEGraphics::clear(u32 colour){
        for(u32 x=0;x<m_width;x++){
            for(u32 y=0;y<m_width;y++){
                write_pixel(x, y, colour);
            }
        }
    }
    void VBEGraphics::write_pixel(u32 x, u32 y, u32 value){
        m_framebuffer[x + y*m_width] = value;
    }
    u32 VBEGraphics::read_pixel(u32 x, u32 y){
        return m_framebuffer[x + y*m_width];
    }
}