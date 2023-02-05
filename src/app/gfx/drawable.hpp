#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SDL2/SDL.h>

class Drawable {
public:
    virtual void draw(SDL_Renderer* renderer) = 0;
};

#endif /* DRAWABLE_HPP */