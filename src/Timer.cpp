#include "include/Timer.h"

Timer::Timer() {
    this->tickInterval = 1.0f;
    this->func = NULL;
    this->active = true;

    this->elapsedDt = 0.0f;
}

Timer::Timer(std::function<void()> onTick, float interval) {
    this->tickInterval = interval;
    this->func = onTick;
    this->active = true;

    this->elapsedDt = 0.0f;
}

void Timer::activate() {
    this->active = true;
}

void Timer::deactivate() {
    this->active = false;
}

void Timer::update(float dt) {
    if (this->active) {
        this->elapsedDt += dt;
        while (this->elapsedDt >= this->tickInterval) {
            this->elapsedDt -= this->tickInterval;

            if (this->func) {
                this->func();
            }
        }
    }
}

void Timer::setCountdown(float extraDt) {
    this->elapsedDt = -extraDt;
}

void Timer::reset() {
    this->elapsedDt = 0.0f;
}

Timer::~Timer() {

}
