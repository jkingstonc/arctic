
#pragma once

#include <kernel/Kernel.h>
#include <util/String.h>

namespace IO{
    // used to write to the serial output for Qemu debugging
    class DbgStream{
    public:
        DbgStream();
        DbgStream(u16 port);
        friend DbgStream& operator<<(DbgStream& ds, String s);
        friend DbgStream& operator<<(DbgStream& ds, const char* s);
        friend DbgStream& operator<<(DbgStream& ds, s32 s);
    private:
        u16 m_port;
    };

    extern DbgStream& operator<<(DbgStream& ds, String s);
    extern DbgStream& operator<<(DbgStream& ds, const char* s);
    extern DbgStream& operator<<(DbgStream& ds, s32 s);
    extern DbgStream dbg_stream;
    extern DbgStream& dbg();
}