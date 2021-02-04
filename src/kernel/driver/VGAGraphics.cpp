#include "VGAGraphics.h"
#include "../io/KPrintf.h"

namespace Driver{

    u8 * VGAGraphics::video_memory = (u8*)0xb8000;

    VGAGraphics::VGAGraphics(){}
    VGAGraphics::~VGAGraphics(){}
    void VGAGraphics::init(){
        IO::kinfo("initialising VGAGraphics driver\n");
    }
    void VGAGraphics::close(){}

    void VGAGraphics::scroll(const u32 l){
        // todo modify the bitmap of the screen and redraw
        constexpr u32 video_memory_max = rows*columns*pixel_depth;
        for(u32 i = 0;i<rows*columns*pixel_depth;i){
            if(i<video_memory_max-columns)
                video_memory[i] = video_memory[i+columns];
        }
    }

    void VGAGraphics::putstr(const s8 * s){
		for(s32 i = 0; s[i];i++)
			putc(s[i]);
    }

    void VGAGraphics::putc(const s8 c){
        if(m_idx >= (columns*rows*pixel_depth))
			m_idx = 0;
		switch(c){
			case '\n': {
				// calculate how far we are along the line
				u32 line_idx = (m_idx/pixel_depth) % columns;
				// move to the start of the next line
				m_idx+= ((columns-line_idx)*pixel_depth);
				break;
			}
			case '\t': {
				m_idx+= (4*pixel_depth);
				break;
			}
			default:{
				video_memory[m_idx]=c;
				video_memory[m_idx+1]=m_colour;
				m_idx+=pixel_depth;
			}
		}
    }
           
    void VGAGraphics::colour(const u8 c){
        m_colour = c;
    }
}