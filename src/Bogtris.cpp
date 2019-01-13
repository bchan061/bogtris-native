#include "include/Bogtris.h"

#include <iostream>
#include <string>

int main(int argc, char* args[]) {
    Window *window = new Window("Test", 640, 480);

    delete window;

    return 0;
}
