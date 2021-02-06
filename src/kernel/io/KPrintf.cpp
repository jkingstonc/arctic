#include "KPrintf.h"
#include "../utils/Math.h"
#include "../Types.h"

extern "C" void kprint_test(int i){
	IO::kprintf("test:\n");
	IO::kprint_int(i);
}

namespace IO{

    const int VGAGreen   = 0x2;
    const int VGACyan    = 0x3;
    const int VGARed     = 0x4;
    const int VGAMagenta = 0x5;

	int idx = 0;
	char * vid_mem = (char*)0xb8000;
	int k_colour = 0;


	void kinfo(const char * info){
		kcolour(VGACyan);
		kprintf("[INFO] ");
		kprintf(info);
	}

	void kwarn(const char * warn){
		kcolour(VGAMagenta);
		kprintf("[WARNING] ");
		kprintf(warn);
	}

	void kerr(const char * err){
		kcolour(VGARed);
		kprintf("[ERROR] ");
		kprintf(err);
	}

	void kclear(){
		idx = 0;
		unsigned int j = 0;

		/* this loops clears the screen
		* there are 25 lines each of 80 columns; each element takes 2 bytes */
		while(j < COLS * LINES * PIX_BYTES) {
			/* blank character */
			vid_mem[j] = ' ';
			/* attribute-byte - light grey on black screen */
			vid_mem[j+1] = 0x07; 		
			j = j + PIX_BYTES;
		}
	}

	void k_cursor_pos(int x, int y){
		idx = x + (COLS*y);
	}

    void kcolour(int colour){
		k_colour = colour;
	}

	void kprintf(const char * msg){
		unsigned int j = 0;
		/* this loop writes the string to video memory */
		while(msg[j] != '\0') {
			switch(msg[j]){
				case '%':
				{
					switch(msg[j+1]){
						case 'd': {
							// print a decimal
						}
						default: {
							kprint_c(msg[j]);
							++j;
							break;
						};
					}
				}
				default: {
					kprint_c(msg[j]);
					++j;
					break;
				}
			}
		}
	}

	void kprint_c(const char c){
		if(idx >= (COLS*LINES*2))
			idx = 0;
		switch(c){
			case '\n': {
				// calculate how far we are along the line
				int line_idx = (idx/PIX_BYTES) % COLS;
				// move to the start of the next line
				idx+= ((COLS-line_idx)*PIX_BYTES);
				break;
			}
			case '\t': {
				idx+= (4*PIX_BYTES);
				break;
			}
			default:{
				vid_mem[idx]=c;
				vid_mem[idx+1]=k_colour;
				idx+=2;
			}
		}
	}

	void kprint_int(int i){
		char buffer[50];
		if(i==0){
			buffer[0]='0';
			buffer[1]='\0';
			IO::kprint_str(buffer);
		}
		
		bool is_neg = i<0;
		if(is_neg)i*=-1;
		//!@TODO for integers larger than 10
		int j =0;
		while(i>0){
			buffer[j]=(i%10)+'0';
			i/=10;
			j++;
		}
		if(is_neg) buffer[j++]='-';
		buffer[j]='\0';
		int start = 0;
		int end = j-1;
		while(start<end){
			char a, b;
			a = *(buffer+start);
			b = *(buffer+end);
			*(buffer+start)=b;
			*(buffer+end)=a;
			start++;
			end--;
		}
		kprint_str(buffer);
	}
    
	void kprint_f(float f, int prescision){
		// extract integer part
		volatile s32 i_part = (s32)f;
		// extraft float part
		//float f_part = (float)f;

		//kprint_int(i_part);
		//kprint_c('.');
		//kprint_int((int)(f_part*Utils::Math::pow(f_part, prescision)));
	}
    
	void kprint_str(const char * str){
		for(int i = 0;str[i];i++)
			kprint_c(str[i]);
	}
}