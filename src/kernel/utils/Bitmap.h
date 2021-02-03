#pragma once

#include "../Types.h"

namespace Utils {

    template <typename T>
    class Bitmap{
        T*data;
        Bitmap(size size);
        ~Bitmap();
    };

}