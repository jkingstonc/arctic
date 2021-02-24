#pragma once

#include <util/Malloc.h>

class RefCounter{
public:
    RefCounter(){
        m_counter=0;
    }
    RefCounter(unsigned int counter){
        m_counter=counter;
    }
    ~RefCounter(){}

    void reset(){
        m_counter=0;
    }
    unsigned int get(){
        return m_counter;
    }
    void operator++(){
        m_counter++;
    }
    void operator++(int){
        m_counter++;
    }
    void operator--(){
        m_counter--;
    }
    void operator--(int){
        m_counter--;
    }
private:
    unsigned int m_counter;
};

template<typename T>
class Ref{
    public:


        static Ref create(T value){
            T* value_ptr = malloc(sizeof(T));
            *value_ptr = value;
            return Ref(value_ptr);
        }

        explicit Ref(T* value=nullptr){
            m_value=value;
            m_ref_counter = (RefCounter*)malloc(sizeof(RefCounter));
            m_ref_counter->reset();
            if(value){
                m_ref_counter++;
            }
        }

        // copy constructor
        Ref(const Ref<T>& other){
            m_value=other.m_value;
            m_ref_counter=other.m_ref_counter;
            m_ref_counter++;
        }


        ~Ref(){
            m_ref_counter--;
            if(m_ref_counter->get()==0){
                free(m_ref_counter);
                free(m_value);
            }
        }
        T* get(){
            return m_value;
        }
        T* operator->(){
            return m_value;
        }
        T& operator*(){
            return *m_value;
        }
        unsigned int count(){
            return m_ref_counter->get();
        }
    private:
        RefCounter* m_ref_counter;
        T* m_value;
};