#include "Timer.h"

Timer::Timer() : running(false) {}

void Timer::reset() {
    running = false;
}

int Timer::start() {
    if (!running) {
        startTime = std::chrono::high_resolution_clock::now();
        running = true;
    }
    return 0; // Opcjonalnie można zwrócić kod statusu
}

int Timer::stop() {
    if (running) {
        endTime = std::chrono::high_resolution_clock::now();
        running = false;
    }
    return 0;
}

int Timer::result() {
    if (running) {
        endTime = std::chrono::high_resolution_clock::now();
    }
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}