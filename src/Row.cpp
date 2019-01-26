#include "include/Row.h"

Row::Row() {
    this->width = 0;
}

Row::Row(int width) {
    this->setWidth(width);
}

Block* Row::getBlock(int x) {
    if (x < 0 || x >= this->width) {
        return NULL;
    }
    return &(this->blocks.at(x));
}

void Row::setWidth(int newWidth) {
    this->width = newWidth;
    this->blocks.clear();
    this->blocks.reserve(newWidth);
    for (int i = 0; i < this->width; i++) {
        this->blocks.push_back(Block());
    }
}

bool Row::isFull() {

}

void Row::reset() {

}

Row::~Row() {
    
}
