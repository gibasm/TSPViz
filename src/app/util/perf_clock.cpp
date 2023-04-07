#include "perf_clock.hpp"

double PerfClock::get_time_delta_ms() const {
    return std::chrono::duration<double, std::milli>(end_tp - start_tp).count();
}

double PerfClock::get_time_delta_us() const {
    return std::chrono::duration<double, std::micro>(end_tp - start_tp).count();
}