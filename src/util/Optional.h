
#pragma once

#include <kernel/Kernel.h>

template <typename T>
class Optional{
private:
    T m_value;
    u1 m_result = false;

public:
    Optional() {}
    Optional(T value) : m_value(value), m_result(true){}
    Optional(T value, u1 result) : m_value(value), m_result(result){}
    
    u1 result(){
        return m_result;
    }

    T value(){
        return m_value;
    }
};