#pragma once

#define LINES     25
#define COLS      80
#define PIX_BYTES 2

namespace IO{
    extern int idx;
    extern char * vid_mem;
    void kclear();
    void kprintf(const char * msg);
    void kprint_c(const char c);
    void kprint_int(int i);
    void kprint_float(float f);
    void kprint_str(const char * str);
}