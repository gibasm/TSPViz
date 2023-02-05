#include "app.hpp"
#include <stdexcept>
#include "gfx/graph.hpp"

static constexpr WindowConfig config = {
    "TSPViz",
    800U,
    600U
};

App::App(const char* instance_file_name) 
:window(config), instance(instance_file_name) {
    graph = std::make_unique<Graph>(instance.get_vertices());
    window.add_to_draw_list(graph.get());
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
    window.show();
}   