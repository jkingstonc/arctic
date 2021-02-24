#include <kernel/dev/Bus.h>

namespace Device{

    Bus::Bus(){}
    Bus::~Bus(){}

    String Bus::name(){
        return "bus";
    }
}