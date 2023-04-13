#ifndef PERF_CLOCK_HPP
#define PERF_CLOCK_HPP

#include <chrono>

/**
 * @brief Rough performance measurement utility. Bear in mind, altough this class 
 * is called a "Performance" clock it does not accurately measure the performance 
 * of certain pieces of code.
 * 
 * @details
 * It is really difficult to percisely measure the performance of some algorithms.
 * The main obstacles are: different scheduling algorithms used by different OSes,
 * compiler optimizations, CPU cache hit rate, out-of-order execution and much more.
 * Creating a 100% accurate benchmark is beyond the scope of this app :(
 * Although if you're interested in benchmarks for embedded systems or microbenchmarks
 * I encourage you to read about them further on the internet, 
 * they are a very fascinating field of study/research :)
 */
class PerfClock {
public:
    constexpr PerfClock() = default;
    virtual ~PerfClock() = default;

    /**
     * @brief Get the time elapsed between the 
     * last calls of PerfClock::start() and PerfClock::stop()
     * 
     * @return elapsed time in milliseconds 
     */
    double get_time_delta_ms() const;

    /**
     * @brief Get the time elapsed between the 
     * last calls of PerfClock::start() and PerfClock::stop()
     * 
     * @return elapsed time in microseconds
     */
    double get_time_delta_us() const;

private:
    typedef std::chrono::high_resolution_clock clk_t;
    typedef std::chrono::time_point<clk_t> tp_t;
    tp_t start_tp, end_tp;

public:
    /**
     * @brief Start measuring the time
     */
    inline void start() {
        start_tp = clk_t::now();    
    }   

    /**
     * @brief Stop measuring the time
     */
    inline void stop() {
        end_tp = clk_t::now();
    }   
};

extern PerfClock perf_clock;

#endif /* PERF_CLOCK_HPP */
