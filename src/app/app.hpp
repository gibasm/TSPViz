#ifndef APP_HPP
#define APP_HPP

#include "gfx/window.hpp"
#include "gfx/graph.hpp"
#include "instance.hpp"
#include "algorithms/tsp_solver.hpp"
#include <thread>

/**
 * @brief Main application class
 * 
 * @details
 * - manages solver creating, 
 * - instance loading,
 * - render and solver threads
 */
class App {
public:
    /**
     * @brief Construct a new App object
     * 
     * @param instance_file_name *.tsp instance file name
     */
    App(const char* instance_file_name);

    virtual ~App();

    /**
     * @brief Runs the application's threads (rendering the graph and running the solver)
     */
    void run();
    
protected:
    void init_SDL();

private:
    MainWindow window;
    std::unique_ptr<TSPSolver> solver;
    std::unique_ptr<Graph> graph;   
    TSPInstance instance;

    std::thread window_thread;
};

#endif /* APP_HPP */
