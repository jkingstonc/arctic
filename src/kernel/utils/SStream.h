#include "String.h"
#include "../Types.h"

class StringStream{
public:
    StringStream();
    ~StringStream();
    String str();
    friend StringStream& operator<<(StringStream& ss, String s);
    friend StringStream& operator<<(StringStream& ss, s32 s);
private:
    String m_str;
};

StringStream& operator<<(StringStream& ss, String s);
StringStream& operator<<(StringStream& ss, s32 s);