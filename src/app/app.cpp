#include "app.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

static constexpr WindowConfig config = {
    "TSPViz",
    800U,
    600U
};


App::App() 
:window(config){}


App::~App() {}


void App::init_SDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Cannot initialize SDL! Reason: " + std::string(SDL_GetError()));
    }
}


void App::run() {
    window.show();
}   