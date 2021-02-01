#include "kprintf.h"


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
			default: {
				/* the character's ascii */
				vid_mem[idx] = msg[j];
				/* attribute-byte: give character black bg and light grey fg */
				vid_mem[idx+1] = 0x07;
				++j;
				idx = idx + 2;
				break;
			}
		}
	}
}