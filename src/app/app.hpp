#ifndef APP_HPP
#define APP_HPP

#include "gfx/window.hpp"
#include "gfx/graph.hpp"
#include "instance.hpp"

class App {
public:
    App(const char* instance_file_name);
    virtual ~App();

    void run();
protected:
    void init_SDL();

private:
    MainWindow window;
    std::unique_ptr<Graph> graph;
    TSPInstance instance;
};

#endif /* APP_HPP */