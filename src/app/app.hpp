#ifndef APP_HPP
#define APP_HPP

#include "gfx/window.hpp"

class App {
public:
    App();
    virtual ~App();

    void run();
protected:
    void init_SDL();

private:
    MainWindow window;
};

#endif /* APP_HPP */