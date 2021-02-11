#pragma once

typedef void u0;
typedef bool u1;
typedef unsigned char u8;
typedef char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef float f32;
typedef double f64;
typedef u32 size;


#define ASSERT(expression, msg) assert(expression, __LINE__, __FILE__, msg)

// used to write to the serial output for Qemu debugging
class DbgStream{
public:
    DbgStream();
    DbgStream(u16 port);
    friend DbgStream& operator<<(DbgStream& ds, const char* s);
    friend DbgStream& operator<<(DbgStream& ds, s32 s);
private:
    u16 m_port;
};

DbgStream& operator<<(DbgStream& ds, const char* s);
DbgStream& operator<<(DbgStream& ds, s32 s);

extern DbgStream dbg_stream;
DbgStream& dbg();
void assert(u1 expression, u32 line, const char* file, const char* msg);