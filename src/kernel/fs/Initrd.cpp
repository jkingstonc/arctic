#include <kernel/fs/Initrd.h>
#include <kernel/io/Debug.h>

namespace FS{

    VFS initrd;
    InitRDHeader* initrd_header;
    InitRDEntry** initrd_files;

    extern void setup_initrd(u32 address){

        initrd.root()->flags = VFS_DIR;

        // get the header
        initrd_header = (InitRDHeader*)address;
        
        u32 current_address = address+(sizeof(InitRDHeader));

        IO::dbg() << "setting up initrd...\n";
        IO::dbg() << "header magic = " << initrd_header->magic << "\n";
        IO::dbg() << "header nfiles = " << initrd_header->n_files << "\n";

        ASSERT(initrd_header->magic==0x123, "initrd invalid magic\n");

        for(u32 i=0;i<initrd_header->n_files;i++){
            initrd_files[i] = (InitRDEntry*)current_address;
            current_address+=sizeof(InitRDEntry);
            IO::dbg() << "file name = " << initrd_files[i]->filename << "\n";
        }
    }

}