#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer {
    private:
        float elapsedDt;
        float tickInterval;
        bool active;
        std::function<void()> func;
    public:
        /**
         * Initializes a blank timer;
         */
        Timer();

        /**
         * Initializes a timer.
         * @param onTick a function to be called on a tick
         */
        Timer(std::function<void()> onTick, float interval);

        /**
         * Updates the timer.
         */
        void update(float dt);

        /**
         * Activates the timer.
         */
        void activate();

        /**
         * Deactivates the timer.
         */
        void deactivate();

        /**
         * Sets any extra time that should be elapsed before starting any tick.
         */
        void setCountdown(float extraDt);

        /**
         * Resets the timer.
         */
        void reset();

        /**
         * Destroys the timer.
         */
        ~Timer();
};

#endif
