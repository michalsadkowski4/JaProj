#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>
#include <functional>

class Timer {
public:
    void Start();
    long long Stop(); 
    static std::string FormatDuration(long long microseconds); 

private:
    std::chrono::high_resolution_clock::time_point start_time;
};

#endif // TIMER_H