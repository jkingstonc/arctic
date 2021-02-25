#pragma once

#include <util/Vector.h>
#include <util/Types.h>
#include <kernel/process/Process.h>
#include <kernel/io/Debug.h>

namespace Process{


    // basic scheduler
    class Scheduler{
    public:
        void next_process(){
            IO::dbg() << "switching process...\n";

            if(m_processes.size()){
            }

            m_counter++;
            if(m_counter>=m_processes.size()) m_counter=0;
        }
    private:
        Vector<Process> m_processes;
        u32 m_counter = 0;
    };
}