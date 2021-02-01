#ifndef KPRINTF_H
#define KPRINTF_H

#define LINES     25
#define COLS      80
#define PIX_BYTES 2


extern int idx;
extern char * vid_mem;
void kclear();
void kprintf(const char * msg);

#endif