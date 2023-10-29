#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>

namespace metrics {

class MeasureTime {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;

public:
    void start();
    void elapsed_time();
};

};