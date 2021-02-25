#pragma once

#include <kernel/Kernel.h>
#include <kernel/process/ThreadPool.h>
#include <util/Ref.h>
#include <kernel/arch/i386/memory/I386Paging.h>


namespace Process {
    class Process{
    public:
        Process(){}
        Process(u32 start){
            m_start=start;
        }
        static const Ref<Process> create_kernel_proc();
        static const Ref<Process> create_user_proc();
        u32 get_pid(){
            return m_pid;
        }
        u1 kill(){
            return m_threads.kill_all();
        }
        ThreadPool* thread_pool(){
            return &m_threads;
        }
        Memory::PageDirectory* page_directory(){
            return &m_page_directory;
        }
    private:
        static u32 pid_counter;
        u32 m_start;                    // the start address of the process        
        u32 m_pid;                      // the process id
        ThreadPool m_threads;           // the thread pool in this process
        Memory::PageDirectory m_page_directory; // the page directory (not a pointer as only this proc can access it)
    };
}