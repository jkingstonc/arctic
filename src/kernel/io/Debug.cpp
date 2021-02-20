#include "Debug.h"
#include "Serial.h"
#include <util/Numeric.h>


namespace IO{
    
    DbgStream dbg_stream;

    DbgStream::DbgStream(){
        m_port = COM1;
    }
    DbgStream::DbgStream(u16 port){
        m_port = port;
    }

    DbgStream& operator<<(DbgStream& ds, String s) {
        auto c_str = s.cstr();
        for(u32 i=0; c_str[i];i++)
            IO::write_serial(ds.m_port, c_str[i]);
        return ds;
    } 

    DbgStream& operator<<(DbgStream& ds, const char* s) {
        for(u32 i=0;s[i];i++)
            IO::write_serial(ds.m_port, s[i]);
        return ds;
    } 

    DbgStream& operator<<(DbgStream& ds, s32 s){
        char buffer[50];
        itoa(s, buffer);
        for(u32 i=0;buffer[i];i++)
            IO::write_serial(ds.m_port, buffer[i]);
        return ds;
    }

    DbgStream& operator<<(DbgStream& ds, u32 s){
        char buffer[50];
        itoa(s, buffer);
        for(u32 i=0;buffer[i];i++)
            IO::write_serial(ds.m_port, buffer[i]);
        return ds;
    }

    DbgStream& dbg(){
        return dbg_stream;
    }
}