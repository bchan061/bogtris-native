#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
    
class Window {
    private:
        int width;
        int height;
        std::string title;

        SDL_Window* window;
        SDL_Surface* windowSurface;
    public:
        /**
         * Initializes a window for SDL.
         * @param title the title of the window
         * @param width the width of the window
         * @param height the height of the window
         */
        Window(std::string title, int width, int height);

        /**
         * Gets the width of the window.
         * @return the width of the window
         */
        int getWidth() { return width; }
        
        /**
         * Gets the height of the window.
         * @return the height of the window
         */
        int getHeight() { return height; }

        /**
         * Gets the title of the window.
         * @return the title of the window
         */
        std::string getTitle() { return title; }

        /**
         * Destroys the window.
         */
        ~Window();
};

#endif
