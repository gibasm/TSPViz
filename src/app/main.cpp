#include "app.hpp"
#include <spdlog/spdlog.h>

int main(void) {
    try {
        App app;
        app.run();
    } catch(const std::runtime_error& exception) {
        spdlog::error(exception.what());
        return 1;
    } 
    return 0;
}