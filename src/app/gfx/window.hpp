#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <inttypes.h>
#include <map>
#include <list>
#include <SDL2/SDL.h>
#include "drawable.hpp"

struct WindowConfig {
    const char* title = "SDL";
    unsigned width = 800;
    unsigned height = 600;
};

typedef void (*EventCallback)(const SDL_Event& event);

/**
 * @brief a wrapper class for SDL_Window and SDL_Renderer
 */
class MainWindow {
public:
    MainWindow(const WindowConfig& config = WindowConfig({}));
    virtual ~MainWindow();

    /**
     * @brief (blocking) creates a window and displays it until some event happens
     */
    void show();

    /**
     * @brief map a SDL event to a callback function
     * 
     * @param event_type SDL_Event::type
     * @param callback callback function void(*)(const SDL_Event& event)
     */
    inline void set_event_callback(uint32_t event_type, EventCallback callback) {
        callbacks.insert(std::make_pair(event_type, callback));
    }

    inline void add_to_draw_list(Drawable* drawable) {
        draw_list.push_back(drawable);
    }

private:
    typedef std::map<uint32_t, EventCallback> CallbackMap;
    typedef std::list<Drawable*> DrawableList;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    WindowConfig config;
    CallbackMap callbacks;
    DrawableList draw_list;
};

#endif /* WINDOW_HPP */