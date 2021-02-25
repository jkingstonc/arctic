#include "Numeric.h"
#include <util/SStream.h>

void itoa(int s, char* buffer){
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

void itoa(unsigned int s, char* buffer){
    if(s==0){
        buffer[0]='0';
        buffer[1]='\0';
    }
    return;
    int j =0;
    while(s>0){
        buffer[j]=(s%10)+'0';
        s/=10;
        j++;
    }
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

void split_float(float value, u32& integer_part, u32& decimal_part, s16& exponent){
    integer_part = (u32)value;
    decimal_part = (u32)((value-integer_part) * 1e9);
    exponent=0;
}

void split_double(double value, u32& integer_part, u32& decimal_part, s16& exponent){
    integer_part = (u32)value;
    decimal_part = (u32)((value-integer_part) * 1e9);
    exponent=0;
}

String to_string(float s){
    // https://blog.benoitblanchon.fr/lightweight-float-to-string/ simple algorithm here

    StringStream ss;

    if(s<0.0){
        ss<<'-';
    }

    u32 integer_part, decimal_part;
    s16 exponent;

    split_float(s, integer_part, decimal_part, exponent);

    ss << (s32)integer_part;

    if(decimal_part!=0){
        ss << "." <<(s32)decimal_part;
    }

    if(exponent<0.0){
        ss << "e-" << (s32)exponent;
    }else{
        ss << "e" << (s32)exponent;
    }

    return ss.str();
}


String to_string(double s){
    // https://blog.benoitblanchon.fr/lightweight-float-to-string/ simple algorithm here

    StringStream ss;

    if(s<0.0){
        ss<<'-';
    }

    u32 integer_part, decimal_part;
    s16 exponent;

    split_float(s, integer_part, decimal_part, exponent);

    ss << (s32)integer_part;

    if(decimal_part!=0){
        ss << "." <<(s32)decimal_part;
    }

    if(exponent<0.0){
        ss << "e-" << (s32)exponent;
    }else{
        ss << "e" << (s32)exponent;
    }

    return ss.str();
}