#pragma once

#include "../kernel/Kernel.h"

#define STRING_INITIAL_ALLOC 50

class String{
public:
    String();
    String(const char* cstr);
    ~String();
    void append(String s);
    void append(const char* s);
    void append(char c);
    int size();
    int length();
    void clear();
    const char* cstr();
    char at(unsigned int pos);
    char operator[](unsigned int pos);
    String* split(char splitter);
    String substr(unsigned int pos, unsigned int len);
    int find(String& s, unsigned int pos=0);
    int find(const char* s, unsigned int pos=0);
    int find(char c, unsigned int pos=0);
private:
    const char * m_cstr;
    u32 m_allocated = 0;
};

u32 strlen(const char* s);