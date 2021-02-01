#pragma once

#define LINES     25
#define COLS      80
#define PIX_BYTES 2

namespace IO{
    extern const int KGreen;
    extern const int KBlue;
    extern const int KRed;
    extern int idx;
    extern char * vid_mem;
    void k_cursor_pos(int x, int y);
    void kclear();
    void kcolour(int colour);
    void kprintf(const char * msg);
    void kprint_c(const char c);
    void kprint_int(int i);
    void kprint_float(float f);
    void kprint_str(const char * str);
}