
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
        friend DbgStream& operator<<(DbgStream& ds, u32 s);
    private:
        u16 m_port;
    };

    extern DbgStream& operator<<(DbgStream& ds, String s);
    extern DbgStream& operator<<(DbgStream& ds, const char* s);
    extern DbgStream& operator<<(DbgStream& ds, s32 s);
    extern DbgStream& operator<<(DbgStream& ds, u32 s);
    extern DbgStream dbg_stream;
    extern DbgStream& dbg();


        // used to write to the serial output for Qemu debugging
    class ErrStream{
    public:
        ErrStream();
        ErrStream(u16 port);
        friend ErrStream& operator<<(ErrStream& ds, String s);
        friend ErrStream& operator<<(ErrStream& ds, const char* s);
        friend ErrStream& operator<<(ErrStream& ds, s32 s);
        friend ErrStream& operator<<(ErrStream& ds, u32 s);
    private:
        const char* ansi_red   = "\u001b[31m";
        const char* ansi_reset = "\u001b[0m";
        u16 m_port;
    };

    extern ErrStream& operator<<(ErrStream& ds, String s);
    extern ErrStream& operator<<(ErrStream& ds, const char* s);
    extern ErrStream& operator<<(ErrStream& ds, s32 s);
    extern ErrStream& operator<<(ErrStream& ds, u32 s);
    extern ErrStream err_stream;
    extern ErrStream& err();
}