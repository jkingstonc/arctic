#include "Math.h"

namespace Utils::Math{
    f32 pow(f32 value, u32 exponent){
        f32 result = value;
        for(u32 i=0;i<exponent;i++)
            result*=value;
        return result;
    }

    s32 pow(s32 value, u32 exponent){
        s32 result = value;
        for(u32 i=0;i<exponent;i++)
            result*=value;
        return result;
    }
}