#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void Timer::Start() {
    start_time = std::chrono::high_resolution_clock::now();
}

long long Timer::Stop() {
    auto end_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
}

std::string Timer::FormatDuration(long long microseconds) {
    std::ostringstream oss;

    if (microseconds < 1000) {
        oss << microseconds << " µs";  // Mikrosekundy
    }
    else if (microseconds < 1000000) {
        double milliseconds = microseconds / 1000.0;
        oss << std::fixed << std::setprecision(3) << milliseconds << " ms";  // Milisekundy
    }
    else {
        double seconds = microseconds / 1000000.0;
        oss << std::fixed << std::setprecision(3) << seconds << " s";  // Sekundy
    }

    return oss.str();
}