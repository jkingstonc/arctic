#include "SStream.h"
#include "Numeric.h"

#include <kernel/io/KPrintf.h>


StringStream::StringStream(){
    m_str=String();
}
StringStream::~StringStream(){}

String StringStream::str(){
    return m_str;
}


StringStream& operator<<(StringStream& ss, const char *s){
    ss.m_str.append(s);
    return ss;
}

StringStream& operator<<(StringStream& ss, String s) {
    ss.m_str.append(s);
    return ss;
} 

StringStream& operator<<(StringStream& ss, u32 s){
    char buffer[50];
    itoa(s,buffer);
    ss.m_str.append(buffer);
    return ss;
}

StringStream& operator<<(StringStream& ss, s32 s){
    char buffer[50];
    itoa(s,buffer);
    ss.m_str.append(buffer);
    return ss;
}

StringStream& operator<<(StringStream& ss, f32 s){
    ss.m_str.append(to_string(s));
    return ss;
}

StringStream& operator<<(StringStream& ss, f64 s){
    ss.m_str.append(to_string(s));
    return ss;
}