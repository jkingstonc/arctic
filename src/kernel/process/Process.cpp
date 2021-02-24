#include <kernel/process/Process.h>
#include <kernel/memory/KMalloc.h>

namespace Process{

    u32 Process::pid_counter = 0;
    
    const Ref<Process> Process::create_kernel_proc(){
        Process* proc = (Process*)Memory::kmalloc(sizeof(Process));
        return Ref<Process>(proc);
    }

    const Ref<Process> Process::create_user_proc(){
        Process* proc = (Process*)Memory::kmalloc(sizeof(Process));
        return Ref<Process>(proc);
    }
    
    u32 Process::get_pid(){
        return m_pid;
    }


}