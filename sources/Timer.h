#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    Timer();      // Konstruktor
    void reset(); // Resetuje timer
    int start();  // Rozpoczyna pomiar czasu
    int stop();   // Kończy pomiar czasu
    int result(); // Zwraca czas w milisekundach

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool running;
};

#endif // TIMER_H