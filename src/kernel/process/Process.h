#pragma once

#include <kernel/Kernel.h>
#include <util/Ref.h>


namespace Process {
    class Process{
    public:
        static const Ref<Process> create_kernel_proc();
        static const Ref<Process> create_user_proc();
        u32 get_pid();
    private:
        static u32 pid_counter;
        u32 m_pid;
    };
}