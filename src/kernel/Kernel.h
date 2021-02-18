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

extern void assert(u1 expression, u32 line, const char* file, const char* msg);
#define ASSERT(expression, msg) assert(expression, __LINE__, __FILE__, msg)
#define ASSERT_REACHED(msg) assert(false, __LINE__, __FILE__, msg)
#define VERSION "0.0.1_a"