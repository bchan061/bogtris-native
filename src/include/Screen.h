#ifndef SCREEN_H
#define SCREEN_H

/* Forward declare Game */
class Game;

class Screen {
    protected:
        Game* game;
    public:
        /**
         * Initializes a new screen.
         */
        Screen(Game* currentGame);

        /**
         * Updates the screen.
         * @param dt the elapsed time from the previous frame, in seconds
         */
        virtual void update(float dt) = 0;
        
        /**
         * Draws the screen.
         * @param alpha the interpolaton factor between the two frames
         */
        virtual void draw(float alpha) = 0;
};

#endif