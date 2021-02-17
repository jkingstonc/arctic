#pragma once

#include "../Types.h"

#define STRING_INITIAL_ALLOC 50

class String{
public:
    String();
    String(const char* cstr);
    ~String();
    void append(String s);
    void append(const char* s);
    int size();
    int length();
    void clear();
    const char* cstr();
private:
    const char * m_cstr;
    u32 m_allocated = 0;
};

u32 strlen(const char* s);