#include "include/Block.h"

Block::Block() {
    this->reset();
}

void Block::reset() {
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->active = false;
}

void Block::set(uint32_t newColor) {
    uint8_t b = newColor & 0xFF;
    uint8_t g = (newColor >> 8) & 0xFF;
    uint8_t r = (newColor >> 16) & 0xFF;

    this->r = r;
    this->g = g;
    this->b = b;
    this->active = true;
}
