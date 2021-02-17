#include "KPrintf.h"
#include "../utils/Math.h"
#include "../Types.h"
#include "../driver/VGAGraphics.h"
#include "Serial.h"

namespace IO{

	void kinfo(const char * info){
		Driver::VGAGraphics::vga_driver.colour(Driver::VGAGraphics::vga_green);
		kprintf("[INFO] ");
		kprintf(info);
	}

	void kwarn(const char * warn){
		Driver::VGAGraphics::vga_driver.colour(Driver::VGAGraphics::vga_red);
		kprintf("[WARNING] ");
		kprintf(warn);
	}

	void kerr(const char * err){
		Driver::VGAGraphics::vga_driver.colour(Driver::VGAGraphics::vga_red);
		kprintf("[ERROR] ");
		kprintf(err);
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
	void kprintf(String msg){
		kprintf(msg.cstr());
	}

	void kprint_c(const char c){
		switch(c){
			default:{
				Driver::VGAGraphics::vga_driver.putc(c);
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