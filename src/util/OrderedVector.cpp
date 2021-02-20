#include <util/OrderedVector.h>

bool default_order_comparitor(void* first, void* second){
    return (int)first < (int)second;
}