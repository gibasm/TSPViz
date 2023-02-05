#ifndef GFX_GRAPH_HPP
#define GFX_GRAPH_HPP

#include "circle.hpp"
#include <memory>
#include <vector>

/**
 * @brief Drawable, graphical representation of a complete graph
 * 
 */
class Graph :public Drawable {
public:
    Graph(std::vector<std::array<float, 2>> instance);
    virtual ~Graph();

    virtual void draw(SDL_Renderer* renderer) override;

    void highlight_edge(size_t start, size_t end, bool highlight = true);

private:
    size_t vertex_count = 0;
    size_t edge_count = 0;
    std::unique_ptr<Circle<16>[]> vertices;
    std::unique_ptr<std::pair<SDL_FPoint, SDL_FPoint>[]> edges;
    std::unique_ptr<SDL_Color[]> edge_colors;
    std::vector<std::shared_ptr<size_t[]>> edge_mapping;
};

#endif /* GFX_GRAPH_HPP */