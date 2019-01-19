#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "MainGameScreen.h"

class Input {
    private:
    
    public:
        /**
         * Initializes an input object.
         */
        Input();

        /**
         * Updates the input.
         * @param dt the time elapsed between frames
         */
        void update(float dt);

        /**
         * Handles a keypress.
         * @param keycode the SDL_Keycode
         */
        void handleKeypress(SDL_Keycode keycode);

        /**
         * Destroys an input object.
         */
        ~Input();
};

#endif