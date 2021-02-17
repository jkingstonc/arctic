#pragma once

#include "Kernel.h"

namespace Kernel {
    class Process{
    public:
        u32 get_pid();
    private:
        u32 m_pid;
    };
}