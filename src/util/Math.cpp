#include <util/Math.h>

float pow(float value, int exponent){
    float result = value;
    for(int i=0;i<exponent;i++)
        result*=value;
    return result;
}

int pow(int value, int exponent){
    int result = value;
    for(int i=0;i<exponent;i++)
        result*=value;
    return result;
}

/*
https://www.geeksforgeeks.org/square-root-of-a-perfect-square/
Babylonian method for quick squareroots
*/
float sqrt(float value){
    float x = value; 
    float y = 1; 
    float e = 0.000001; // accuracy level
    while (x - y > e) { 
        x = (x + y) / 2; 
        y = value / x; 
    } 
    return x; 
}