#include "string.h"

namespace std{
    string::string(){
    }
    string::string(char* cstr){
        m_cstr=cstr;
    }
    string::~string(){}

    int string::size(){
        return 0;
    }

    int string::length(){
        return 0;
    }

    void clear(){}

    const char* string::cstr(){
        return m_cstr;
    }
}