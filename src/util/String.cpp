#include <util/String.h>
#include <util/Malloc.h>

#define STRING_INIT_SIZE 25

String::String(){
    m_size=0;
    m_cstr = (char*)malloc(STRING_INIT_SIZE);
    m_allocated = STRING_INIT_SIZE;
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
    char* new_str = (char*)malloc(strlen(m_cstr)+s.length()+1);
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
    char* new_str = (char*)malloc(strlen(m_cstr)+strlen(s)+1);
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
    //free((void*)s);
    clear();
}

void String::append(char c){

}

char String::at(unsigned int pos){
    return m_cstr[pos];
}

char String::operator[](unsigned int pos){
    return m_cstr[pos];
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

String String::substr(unsigned int pos, unsigned int len=0){
    String s;
    if (len==0){
        len = size()-pos;
    }
    for(int i=pos;i<len;i++){
        s.append(m_cstr[i]);
    }
    return s;
}

int String::find(String& s, unsigned int pos){
    unsigned int str_len = strlen(m_cstr);
    for(int i=pos;i<size();i++){
        if(m_cstr[i]==s.at(0)){
            // check if the rest of the string matches
            bool found = true;
            for(int j=1;j<s.size();j++){
                if(i+j >= str_len || m_cstr[i+j]!=s.at(j)){
                    found=false;
                    break;
                }
            }
            if(found){
                return i;
            }
        }
    }
    return -1;
}
int String::find(const char* s, unsigned int pos){
    unsigned int str_len = strlen(m_cstr);
    for(int i=pos;i<size();i++){
        if(m_cstr[i]==s[0]){
            // check if the rest of the string matches
            bool found = true;
            for(int j=1;j<strlen(s);j++){
                if(i+j >= str_len || m_cstr[i+j]!=s[j]){
                    found=false;
                    break;
                }
            }
            if(found){
                return i;
            }
        }
    }
    return -1;
}
int String::find(char c, unsigned int pos){
    for(int i=pos;i<size();i++){
        if(m_cstr[i]==c)
            return i;
    }
    return 0;
}

u32 strlen(const char* s){
    u32 counter=0;
    while(s[counter]) counter++;
    return counter;
}