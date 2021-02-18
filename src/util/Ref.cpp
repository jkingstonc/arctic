#include "Ref.h"

#include <kernel/memory/KMalloc.h>

Ref::Ref(){
    m_counter = (u32*)Memory::kmalloc(sizeof(u32));
    *m_counter++;
}
Ref::Ref(u32 counter){
    m_counter = (u32*)Memory::kmalloc(sizeof(u32));
    *m_counter=counter;
}
Ref::~Ref(){
    *m_counter--;
}
u32 Ref::counter(){
    return *m_counter;
}