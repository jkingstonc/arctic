#include "Shell.h"
#include "../io/KPrintf.h"

namespace Shell{
    Shell Shell::create(){
        return {};
    }

    int Shell::exec(const char * cmd){
        IO::kprint_str(cmd);
        return 0;
    }

    void Shell::run(){
        IO::kprint_str(">");
    }
}