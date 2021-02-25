#include <user/Driver.h>
#include <util/Malloc.h>

namespace Driver{

    class EXT2 : public Driver {
    public:
        static Ref<EXT2> create(){
            EXT2* ext2 = (EXT2*)malloc(sizeof(EXT2));
            Driver::register_driver(ext2);
            return Ref<EXT2>(ext2);
        }
        String name() override{
            return "ext2";
        }
    private:
    };
    
}