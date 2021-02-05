#include "Panic.h"

#include "io/KPrintf.h"
#include "dev/Video.h"

namespace Kernel{
    u8 panic(const char* msg){
        // set video mode VGA
        Device::set_video_mode(Device::VideoMode::VGA);
        IO::kerr(msg);
        return 0;
    }
}