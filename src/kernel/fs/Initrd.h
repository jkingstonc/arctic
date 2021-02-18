#pragma once

#include <kernel/fs/vfs.h>


// initrd (init ram disk) is the first VFS loaded into memory when the kernel starts

namespace FS{


    // this is the header format of the initial ram disk filesystem header
    struct InitRDHeader{
        u32 n_files; // number of files
        u32 magic;
    } __attribute__((packed));

    // this is the header for an initrd entry
    struct InitRDEntry{
        const char* filename;
        u32 offset; // offset from the header address
        u32 length; // length of the file
    } __attribute__((packed));




    // read the ram disk image at the address into a VFS
    extern void setup_initrd(u32 address);

    // this is the initial ram disk virtual filesystem
    extern VFS initrd; 
    extern InitRDHeader* initrd_header;
    extern InitRDEntry** initrd_files;
}