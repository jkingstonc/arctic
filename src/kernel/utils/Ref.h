#pragma once

#include "../Types.h"

class Ref{
public:
    Ref();
    Ref(u32 counter);
    ~Ref();
    u32 counter();
private:
    u32 *m_counter;
};