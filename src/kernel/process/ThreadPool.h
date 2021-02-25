#pragma once

#include <util/Types.h>
#include <util/Vector.h>
#include <kernel/Process/Thread.h>
#include <util/Ref.h>

namespace Process{

    class ThreadPool{
    public:
        u1 kill_all(){
            for(s32 i=0;i<m_size;i++){
                m_threads[i]->kill();
            }
            return true;
        }
    private:
        Vector<Ref<Thread>> m_threads;
        u32 m_size = 0;
    };
}