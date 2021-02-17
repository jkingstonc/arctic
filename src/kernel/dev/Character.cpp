#include "Character.h"


namespace Device{
    CharacterDevice::CharacterDevice(){}
    CharacterDevice::~CharacterDevice(){}
    u8 CharacterDevice::read(){return 0;}
    void CharacterDevice::write(u8 c){}
}