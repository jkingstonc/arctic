#include "String.h"
#include "../kernel/memory/KMalloc.h"

String::String(){
}
String::String(const char* cstr){
    m_cstr=cstr;
    m_allocated = strlen(cstr)+1;
}
String::~String(){
    // !@TODO implement kfree
    // Memory::kfree(m_cstr);
}

void String::append(String s){
    // allocate enough space for the new string
    char* new_str = (char*)Memory::kmalloc_aligned(strlen(m_cstr)+s.length()+1);
    u32 i;
    for (i=0;i<strlen(m_cstr);i++){
        new_str[i]=m_cstr[i];
    }
    u32 j;
    for(j=0;j<s.length();j++){
        new_str[i+j]=s.cstr()[j];
    }
    new_str[i+j+1]='\0';
    m_cstr=new_str;

    // deallocate ourself and the other string
    s.clear();
    clear();
}


void String::append(const char* s){
    // allocate enough space for the new string
    char* new_str = (char*)Memory::kmalloc_aligned(strlen(m_cstr)+strlen(s)+1);
    u32 i;
    for (i=0;i<strlen(m_cstr);i++){
        new_str[i]=m_cstr[i];
    }
    u32 j;
    for(j=0;j<strlen(s);j++){
        new_str[i+j]=s[j];
    }
    new_str[i+j+1]='\0';
    m_cstr=new_str;
    // deallocate ourself and the other string
    //Memory::kfree(s);
    clear();
}

int String::size(){
    return m_allocated;
}

int String::length(){
    return strlen(m_cstr);
}

void String::clear(){}

const char* String::cstr(){
    return m_cstr;
}


u32 strlen(const char* s){
    u32 counter=0;
    while(s[counter]) counter++;
    return counter;
}