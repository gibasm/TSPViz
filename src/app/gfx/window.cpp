#include "window.hpp"
#include <stdexcept>
#include <string>

MainWindow::MainWindow(const WindowConfig& config) {
    this->config = config;
}

MainWindow::~MainWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

inline void MainWindow::set_event_callback(uint32_t event_type, EventCallback callback) {
    callbacks.insert(std::make_pair(event_type, callback));
}

void MainWindow::show() {
    window = SDL_CreateWindow(
        config.title, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        config.width, 
        config.height, 
        SDL_WINDOW_SHOWN
    );

    if(window == nullptr) {
        throw std::runtime_error("Cannot open a window! Reason:" + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(renderer == nullptr) {
        throw std::runtime_error("Cannot open a renderer! Reason:" + std::string(SDL_GetError()));
    }

    bool open = true;
    SDL_Event event;
    while(open) {

        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                open = false;
                break;
            }
            /* find if a event is mapped to a callback */
            if(callbacks.find(event.type) != callbacks.end()) {
                callbacks.at(event.type)(event);
            }
        } /* while */

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    } /* while */

}