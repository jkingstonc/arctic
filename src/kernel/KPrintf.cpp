#include "KPrintf.h"

namespace IO{
	int idx = 0;
	char * vid_mem = (char*)0xb8000;

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

	void kprintf(const char * msg){
		unsigned int j = 0;
		/* this loop writes the string to video memory */
		while(msg[j] != '\0') {
			switch(msg[j]){
				case '\n': {
					// calculate how far we are along the line
					int line_idx = (idx/PIX_BYTES) % COLS;
					// move to the start of the next line
					idx+= ((COLS-line_idx)*PIX_BYTES);
					++j;
					break;
				}
				case '\t': {
					idx+= (4*PIX_BYTES);
					++j;
					break;
				}
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
		vid_mem[idx]=c;
		vid_mem[idx+1]=0x07;
		idx+=2;
	}

	void kprint_int(int i){
		char buffer[50];
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
    
	void kprint_float(float f){}
    
	void kprint_str(const char * str){
		for(int i = 0;str[i];i++)
			kprint_c(str[i]);
	}
}