#include "String.h"
#include <kernel/Kernel.h>

class StringStream{
public:
    StringStream();
    ~StringStream();
    String str();
    friend StringStream& operator<<(StringStream& ss, const char *s);
    friend StringStream& operator<<(StringStream& ss, String s);
    friend StringStream& operator<<(StringStream& ss, u32 s);
    friend StringStream& operator<<(StringStream& ss, s32 s);
    friend StringStream& operator<<(StringStream& ss, f32 s);
    friend StringStream& operator<<(StringStream& ss, f64 s);
private:
    String m_str;
};

StringStream& operator<<(StringStream& ss, const char *s);
StringStream& operator<<(StringStream& ss, String s);
StringStream& operator<<(StringStream& ss, u32 s);
StringStream& operator<<(StringStream& ss, s32 s);
StringStream& operator<<(StringStream& ss, f32 s);
StringStream& operator<<(StringStream& ss, f64 s);