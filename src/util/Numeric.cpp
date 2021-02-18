#include "Numeric.h"

void itoa(s32 s, char* buffer){
    if(s==0){
        buffer[0]='0';
        buffer[1]='\0';
    }
    bool is_neg = s<0;
    if(is_neg)s*=-1;

    int j =0;
    while(s>0){
        buffer[j]=(s%10)+'0';
        s/=10;
        j++;
    }
    if(is_neg) buffer[j++]='-';
    buffer[j]='\0';
    int start = 0;
    int end = j-1;
    while(start<end){
        char a, b;
        a = *(buffer+start);
        b = *(buffer+end);
        *(buffer+start)=b;
        *(buffer+end)=a;
        start++;
        end--;
    }
}