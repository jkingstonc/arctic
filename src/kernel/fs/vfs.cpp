#include <kernel/fs/vfs.h>
#include <kernel/io/Debug.h>

namespace FS{
    VFS::VFS(){}
    VFS::~VFS(){}

    VFSNode* VFS::root(){
        return &m_root;
    }


    u32 read_vfs_file(VFSNode* node, u32 offset, u32 size, u8* buffer){
        IO::dbg() << "read file = " << node->filename << "\n";
        if(node->read){
            return node->read(node,offset, size, buffer);
        }
        return 0;
    }

    u32 write_vfs_file(VFSNode* node, u32 offset, u32 size, u8* buffer){
        IO::dbg() << "write file = " << node->filename << "\n";
        if(node->write){
            return node->write(node, offset, size, buffer);
        }
        return 0;
    }

    void open_vfs_file(VFSNode* node, u32 read, u32 write){
        IO::dbg() << "open file = " << node->filename << "\n";
        if(node->open){
            node->open(node);
        }
    }

    void close_vfs_file(VFSNode* node){
        IO::dbg() << "closing file = " << node->filename << "\n";
        if(node->close){
            node->close(node);
        }
    }
}