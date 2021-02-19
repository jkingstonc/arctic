#pragma once

#include <util/Malloc.h>

#define VECTOR_INIT_SIZE 10

template<typename T>
class Vector{
public:
    Vector(){
        m_data = (T*)malloc(VECTOR_INIT_SIZE * sizeof(T));
        m_allocated = VECTOR_INIT_SIZE;
    }
    
    ~Vector(){
        for(int i=0;i<m_size;i++){
            m_data[i].~T();
        }
        free(m_data);
    }

    T at(unsigned int index){
        return m_data[index];
    }

    void clear(){
        for(int i=0;i<m_size;i++){
            m_data[i].~T();
            m_data[i]=0;
        }
        m_size=0;
    }

    void push_back(T elem){
        if(m_size+1 > m_allocated){
            m_allocated+=VECTOR_INIT_SIZE;
            m_data=(T*)realloc(m_data, m_allocated*sizeof(T));
        }
        m_data[m_size]=elem;
        m_size++;
    }

    unsigned int size(){
        return m_size;
    }
private:
    T* m_data;
    unsigned int m_size = 0;
    unsigned int m_allocated = 0;
};