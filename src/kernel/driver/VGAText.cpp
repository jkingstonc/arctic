#include "VGAText.h"
#include "../io/KPrintf.h"
#include "../io/Port.h"

namespace Driver{

    VGAText VGAText::vga_text = VGAText();

    u8 * VGAText::video_memory = (u8*)0xb8000;


    VGAText::VGAText(){}
    VGAText::~VGAText(){}
    void VGAText::init(){
        enable_cursor(true);
        IO::kinfo("initialised VGAGraphics");
    }
    void VGAText::close(){}

    void VGAText::scroll(const u32 l){
        u32 max_memory = rows*columns*pixel_depth;
        for(u32 i = 0;i<rows*columns*pixel_depth; i++){
            if(i<rows*columns*pixel_depth - (columns*pixel_depth))
                video_memory[i] = video_memory[i+columns*pixel_depth];
        }
    }

    void VGAText::clear(const u8 c){
        colour(c);
        for(u32 i=0;i<columns*rows*pixel_depth;i++)
            video_memory[i]=0;
        set_cursor_pos(0,0);
        m_idx=0;
    }

    void VGAText::putstr(const s8 * s){
		for(s32 i = 0; s[i];i++)
			putc(s[i]);
    }

    void VGAText::putc(const s8 c){
        // if we have overran the buffer,then reset the index to 1 row before the end
        if(m_idx > (columns*rows*pixel_depth)){
           m_idx=(columns*rows*pixel_depth)-(columns*pixel_depth);
           scroll(1);
        }
		switch(c){
			case '\n': {
				// calculate how far we are along the line
				u32 col = (m_idx/pixel_depth) % columns;
				// move to the start of the next line
				m_idx+= ((columns-col)*pixel_depth);
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
        u32 column = m_idx % columns;
        u32 row = m_idx/columns;
        set_cursor_pos(column, row);
    }
           
    void VGAText::colour(const u8 c){
        m_colour = c;
    }

    void VGAText::enable_cursor(u1 enabled=true){
        if(enabled){

            // set max scan line register to 15
            IO::outb(0x3d4, 0x09);
            IO::outb(0x3d5, 0x0f);

            // set cursor end line to 15
            IO::outb(0x3d4, 0x0b);
            IO::outb(0x3d5, 0x0f);

            // set start line to 14 and enable visibility
            IO::outb(0x3d4, 0x0a);
            IO::outb(0x3d5, 0x0e);
        }else{
            IO::outb(0x3d4, 0x0a);
            IO::outb(0x3d5, 0x20);
        }
    }

    void VGAText::set_cursor_pos(u32 x, u32 y){
        u16 pos = y * columns + x;
        m_idx = pos;
        IO::outb(0x3d4, 0x0f);
        IO::outb(0x3d5, (u8)(pos & 0xff));
        IO::outb(0x3d4, 0x0e);
        IO::outb(0x3d5, (u8)((pos >> 8) & 0xff));
    }

    u16 VGAText::get_cursor_pos(){
        u16 pos = 0;
        IO::outb(0x3d4, 0x0f);
        pos |= IO::inb(0x3d5);
        IO::outb(0x3d4, 0x0e);
        pos |= ((u16)IO::inb(0x3d5)) << 8;
        return pos;
    }
}