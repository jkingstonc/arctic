#pragma once

#include <util/Types.h>
//#include <kernel/process/Process.h>

namespace Process{

    class Process;
    
    class Thread{
    public:
        u1 kill(){
            return true;
        }
        u1 join(){
            return true;
        }
    private:
        Process* m_process;
    };
}