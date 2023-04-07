#include "app.hpp"
#include <stdexcept>
#include "gfx/graph.hpp"
#include "util/ini_loader.hpp"
#include "algorithms/solver_factory.hpp"
#include <spdlog/spdlog.h>

static const char* INI_FILE_NAME = "config.ini";

static constexpr WindowConfig config = {
    "TSPViz",
    800U,
    600U
};

App::App(const char* instance_file_name) 
:window(config), instance(instance_file_name) {
    init_SDL();

    graph = std::make_unique<Graph>(instance.get_vertices());
    window.add_to_draw_list(graph.get());

    auto ini = load_config(INI_FILE_NAME);
    solver = TSPSolverFactory::create(instance, *graph, ini);

    window_thread = std::thread([&]() { this->window.show(); });
}


App::~App() {
    SDL_Quit();
}


void App::init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Cannot initialize SDL! Reason: " + std::string(SDL_GetError()));
    }
}


void App::run() {
    perf_clock.start();
    solver->solve();
    perf_clock.stop();

    window_thread.join();

    spdlog::info("Time elapsed: {} ms", perf_clock.get_time_delta_ms());
}   