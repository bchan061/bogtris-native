#include "include/Window.h"

Window::Window(std::string title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
    this->running = true;

    /* Initialize SDL. */
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

        /* Initialize the window. */
        if (this->window == NULL) {
            SDL_Log("Unable to create SDL window. (%s)", SDL_GetError());
        } else {
            this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
            if (this->renderer == NULL) {
                SDL_Log("Unable to create SDL renderer. (%s)", SDL_GetError());
            }
            this->windowSurface = SDL_GetWindowSurface(this->window);
            SDL_UpdateWindowSurface(this->window);
        }
    }
}

void Window::handleKeyPress(SDL_Keycode keycode) {
    
}

void Window::run() {
    SDL_Event e;
    /* Game loop */
    while (this->running) {
        /* Handle events */
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    this->running = false;
                    break;
                case SDL_KEYDOWN:
                    this->handleKeyPress(e.key.keysym.sym);
                    break;
                default:
                    break;
            }
        }

        /* Clear the window surface to black */
        SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
        SDL_RenderClear(this->renderer);
        this->game->update(SDL_GetTicks());
        SDL_RenderPresent(this->renderer);
    }
}

void Window::attachGame(Game* newGame) {
    this->game = newGame;
    this->game->attachRenderer(this->renderer);
}

Window::~Window() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
    }

    delete this->game;
    this->game = NULL;

    SDL_Quit();
}
