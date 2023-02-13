#include "app.hpp"
#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        spdlog::error("Usage: tspviz <instance>.tsp");
        return 1;
    }
    if((argc == 3) && (std::string("-d").compare(argv[2]) == 0)) {
        spdlog::set_level(spdlog::level::debug);
    }

    try {
        App app(argv[1]);
        app.run();
    } catch(const std::runtime_error& exception) {
        spdlog::error(exception.what());
        return 2;
    }

    return 0;
}