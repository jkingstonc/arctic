#pragma once

#define LINES     25
#define COLS      80
#define PIX_BYTES 2

#define CYAN  0x3
#define GREEN 0x2
#define RED   0x4

namespace IO{

    // used for debugging
    class DbgStream{
    public:
        DbgStream* operator<<(char *s);
        DbgStream* operator<<(int *i);
    };


    extern const int VGAGreen;
    extern const int VGACyan;
    extern const int VGARed;
    extern int idx;
    extern char * vid_mem;
    void kinfo(const char * info);
    void kwarn(const char * war);
    void kerr(const char * err);
    void k_cursor_pos(int x, int y);
    void kclear();
    void kcolour(int colour);
    void kprintf(const char * msg);
    void kprint_c(const char c);
    void kprint_int(int i);
    void kprint_f(float f, int prescision);
    void kprint_str(const char * str);
}