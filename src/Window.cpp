#include "include/Window.h"

Window::Window(std::string title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL. (%s)", SDL_GetError());
    } else {
        this->window = SDL_CreateWindow(
            this->title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            this->width,
            this->height,
            SDL_WINDOW_SHOWN
        );

        if (this->window == NULL) {
            SDL_Log("Unable to create SDL window. (%s)", SDL_GetError());
        } else {
            this->windowSurface = SDL_GetWindowSurface(window);

            /* Testing */
            SDL_FillRect(this->windowSurface, NULL, SDL_MapRGB(this->windowSurface->format, 0x00, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(this->window);

            SDL_Delay(2000);
        }
    }
}

Window::~Window() {
    if (this->window != NULL) {
        SDL_DestroyWindow(this->window);
    }

    SDL_Quit();
}
