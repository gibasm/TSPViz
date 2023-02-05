#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "drawable.hpp"
#include <cmath>

/**
 * @brief Simple, white circle. Used to represent graph vertices.
 * 
 * @tparam N number of points of the circle 
 */
template <size_t N = 64> 
class Circle :public Drawable {
public:
    constexpr Circle(float radius = 1.0f, SDL_FPoint center = {0.0f, 0.0f}) {
        this->center = center;
        float t = 0.0f;
        float increase = (2.0f*M_PI) / static_cast<float>(N-1);
        for(size_t i = 0; i < N; ++i) {
            points[i].x = radius * sinf(t) + center.x;
            points[i].y = radius * cosf(t) + center.y;
            t += increase;
        }
    }

    virtual ~Circle() {} 

    SDL_FPoint get_center() {
        return center;
    }

    virtual void draw(SDL_Renderer* renderer) override {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLinesF(renderer, points, N);
    }
    
private:
    SDL_FPoint points[N];
    SDL_FPoint center;
};

#endif /* CIRCLE_HPP */