#pragma once



namespace std{
    class string{
    public:
        string();
        string(char* cstr);
        ~string();
        int size();
        int length();
        void clear();
        const char* cstr();
    private:
        char * m_cstr;
    };
}