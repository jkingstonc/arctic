#pragma once

#include <util/String.h>
#include <kernel/Kernel.h>

#define VFS_FILE       0x1
#define VFS_DIR        0x2
#define VFS_CHARDEV    0x3
#define VFS_BLOCKDEV   0x4
#define VFS_PIPE       0x5
#define VFS_SYMLINK    0x6
#define VFS_MOUNTPOINT 0x8



namespace FS{

    struct VFSNode;

    // standard POSIX file descriptor callbacks
    typedef u32 (*read_callback)(VFSNode*, u32, u32, u8*);
    typedef u32 (*write_callback)(VFSNode*, u32, u32, u8*);
    typedef void (*open_callback)(VFSNode*);
    typedef void (*close_callback)(VFSNode*);

    extern u32 read_vfs_file(VFSNode* node, u32 offset, u32 size, u8* buffer);
    extern u32 write_vfs_file(VFSNode* node, u32 offset, u32 size, u8* buffer);
    extern void open_vfs_file(VFSNode* node, u32 read, u32 write);
    extern void close_vfs_file(VFSNode* node);

    struct VFSNode{
        const char* filename; // filename
        u32 permissions;      // file permission flags  
        u32 uid;              // file user owner id
        u32 gid;              // file group owner id
        u32 flags;            // e.g. file, directory
        u32 inode;            // points to filesystem specific inode identifier
        u32 size;
        u32 implementation;   // implementation specific number
        VFSNode* children;    // store directory entries, or if this is a symlink then the symlink

        // POSIX compliant callbacks
        read_callback read = 0;
        write_callback write = 0;
        open_callback open = 0;
        close_callback close = 0;

    };

    class VFS{
    public:
        VFS();
        ~VFS();
        VFSNode* root();
        VFSNode* get_file(String path); // given a path (/dev/null) return the VFSNode*
    private:
        VFSNode m_root;
    };
}