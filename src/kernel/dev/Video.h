#pragma once

#include "../Types.h"

namespace Device{

    enum class VideoMode{
        VGA,
        GOP,
        VESA,
    };

    u8 set_video_mode(VideoMode mode);
}