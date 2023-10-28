#include "measure_time.h"

namespace metrics {

void MeasureTime::start() {
    m_start_time = std::chrono::high_resolution_clock::now();
}

void MeasureTime::elapsed_time() {
    m_end_time = std::chrono::high_resolution_clock::now();

    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(m_end_time - m_start_time).count() * 1e-9;

    std::cout << "[INFO]: Time taken: " << std::fixed << time_taken << std::setprecision(9) << "sec" << std::endl;
}

};