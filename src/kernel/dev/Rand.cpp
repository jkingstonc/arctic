#include <kernel/dev/Rand.h>

namespace Device{
    u8 Rand::read(){
        return 0;
    }
    void Rand::write(u8 c){
        m_seed=c*0x12234 % 232345;
    }
    
    String Rand::name(){
        return "random";
    }
}