#include "graph.hpp"
#include <array>
#include <cassert>

/* TODO: move the window dimensions somewhere else */
#define WIDTH 800
#define HEIGHT 600

#define DEFAULT_COLOR {0x41, 0x41, 0x41, 0x40}
#define HIGHLIGHT_COLOR {0xFF, 0x41, 0x41, 0xFF}

Graph::Graph(std::vector<std::array<float, 2>> instance) {
    this->vertex_count = instance.size();

    vertices = std::make_unique<Circle<16>[]>(vertex_count);

    float max_x = 0, max_y = 0;
    for(auto& v : instance) {
        max_x = std::max(v[0], max_x);
        max_y = std::max(v[1], max_y);
    }

    for(size_t i = 0; i < vertex_count; ++i) {
        float x = (instance.at(i)[0] / max_x) * WIDTH;
        float y = (instance.at(i)[1] / max_y) * HEIGHT; 
        vertices[i] = Circle<16>(5.0f, {x, y});
    }

    edge_count = vertex_count*(vertex_count-1) / 2;

    edges = std::make_unique<std::pair<SDL_FPoint, SDL_FPoint>[]>(edge_count);
    edge_colors = std::make_unique<SDL_Color[]>(edge_count);
    
    for(size_t i = 0; i < vertex_count; ++i) {
        edge_mapping.push_back(std::make_unique<size_t[]>(vertex_count));
    }

    size_t edge_no = 0;

    for(size_t i = 0; i < vertex_count; ++i) {
        SDL_FPoint start = vertices[i].get_center();
        for(size_t j = i+1; j < vertex_count; ++j) {
            edge_mapping[i][j] = edge_no;
            edge_mapping[j][i] = edge_no;

            SDL_FPoint end = vertices[j].get_center();
            edges[edge_no] = std::make_pair(start, end);
            edge_colors[edge_no] = DEFAULT_COLOR;
            ++edge_no;
        }
    }

}

Graph::~Graph() {

}

void Graph::highlight_edge(size_t start, size_t end, bool highlight) {
    assert(start != end);
    if(highlight) {
        edge_colors[edge_mapping[start][end]] = HIGHLIGHT_COLOR;
        return;
    }

    edge_colors[edge_mapping[start][end]] = DEFAULT_COLOR;
}

void Graph::draw(SDL_Renderer* renderer) {
    for(size_t i = 0; i < edge_count; ++i) {
        SDL_SetRenderDrawColor(renderer, 
            edge_colors[i].r, edge_colors[i].g, edge_colors[i].b, 
            edge_colors[i].a);
        SDL_RenderDrawLine(renderer, 
            edges[i].first.x, edges[i].first.y, 
            edges[i].second.x, edges[i].second.y);
    }

    for(size_t i = 0; i < vertex_count; ++i) {
        vertices[i].draw(renderer);
    }
    
}