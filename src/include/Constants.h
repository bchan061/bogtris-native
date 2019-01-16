#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cstdint>

namespace Constants {
    int const SCREEN_WIDTH = 800;
    int const SCREEN_HEIGHT = 600;
    int const FRAMES_PER_SECOND = 60;
    float const SECONDS_PER_FRAME = 1.0f / Constants::FRAMES_PER_SECOND;

    namespace Colors {
        uint32_t const CYAN = 0x00FFFF;
        uint32_t const BLUE = 0x0000FF;
        uint32_t const ORANGE = 0xFF8000;
        uint32_t const YELLOW = 0xFFFF00;
        uint32_t const GREEN = 0x00FF00;
        uint32_t const PURPLE = 0x800080;
        uint32_t const RED = 0xFF0000;
        uint32_t const GRAY = 0x999999;
    }
}

#endif