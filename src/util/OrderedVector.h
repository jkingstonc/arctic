#pragma once


#include <util/Malloc.h>
#include <kernel/Kernel.h>
#include <kernel/io/Debug.h>

#define ORDERED_VECTOR_INIT_SIZE 10

// template<typename T>
// using order_comparison = bool (*order_comparison_fn)(T first, T second);


// bool int_order_comparison(int first, int second){
//     return first < second;
// }



template<typename T>
class OrderedVector{
public:
    OrderedVector(){
        //set_comparitor(int_order_comparison);
        m_data = (T*)malloc(ORDERED_VECTOR_INIT_SIZE * sizeof(T));
        m_allocated = ORDERED_VECTOR_INIT_SIZE;
    }
    ~OrderedVector(){
        for(int i=0;i<m_size;i++){
            m_data[i].~T();
        }
        free(m_data);
    }
    void put(T data){

        if(m_size+1 > m_allocated){
            m_allocated+=ORDERED_VECTOR_INIT_SIZE;
            m_data=(T*)realloc(m_data, m_allocated*sizeof(T));
        }

        // find the index where we can insert into
        unsigned int idx=0;
        while(idx<m_size && m_data[idx]<data){
            IO::dbg() << "comparing "<<data<< " with "<<m_data[idx]<<"... result "<< (m_data[idx]>data) <<"\n";
            idx++;
        }
        
        IO::dbg() << "inserting into index ="<<idx<<"m_size =" << m_size <<"\n";
        // found the idx
        if(idx==m_size){
            m_data[idx]=data;
        }else{
            T tmp_data1 = m_data[idx];
            m_data[idx]=data;
            // shift each element along one
            while(idx<=m_size){
                idx++;
                T tmp_data2 = m_data[idx];
                m_data[idx]=tmp_data1;
                tmp_data1=tmp_data2;
            }
        }
        m_size++; 
    }
    T operator[](unsigned int index){
        return m_data[index];
    }
    T lookup(unsigned int index){
        return m_data[index];
    }
    void remove(unsigned int index){
        for(int i=index;i<m_size;i++)
            m_data[i]=m_data[i+1];
        m_size--;
    }
    unsigned int size(){
        return m_size;
    }
    void clear(){
        for(int i=0;i<m_size;i++){
            m_data[i].~T();
            m_data[i]=0;
        }
        m_size=0;
    }
private:
    T* m_data;
    unsigned int m_size = 0; // the actual space used
    unsigned int m_allocated = 0; // the space we have allocated
    //order_comparison m_comparitor;
};