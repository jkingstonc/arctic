#pragma once

#include "../../util/String.h"

#define LINES     25
#define COLS      80
#define PIX_BYTES 2

#define CYAN  0x3
#define GREEN 0x2
#define RED   0x4

namespace IO{
    extern const int VGAGreen;
    extern const int VGACyan;
    extern const int VGARed;
    extern int idx;
    extern char * vid_mem;
    void kinfo(const char * info);
    void kinfo(String info);
    void kwarn(const char * war);
    void kerr(const char * err);
    void kclear();
    void kprintf(const char * msg);
    void kprintf(String msg);
    void kprint_c(const char c);
    void kprint_int(int i);
    void kprint_f(float f, int prescision);
    void kprint_str(const char * str);
}