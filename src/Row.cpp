#include "include/Row.h"

Row::Row() {
    this->width = 0;
    this->blocks = NULL;
}

Row::Row(int width) {
    this->setWidth(width);
}

Block* Row::getBlock(int x) {
    if (x < 0 || x >= this->width) {
        return NULL;
    }
    return &(this->blocks[x]);
}

void Row::setWidth(int newWidth) {
    this->width = newWidth;
    if (this->blocks) {
        delete[] this->blocks;
    }

    this->blocks = new Block[this->width];
}

Row::~Row() {
    if (this->blocks) {
        delete[] this->blocks;
    }
}
