#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include <memory>
#include <vector>
#include <array>

/* aka neighborhood matrix */
typedef std::vector<std::vector<float>> GraphMatrix;

/**
 * @brief TSP problem instance
 */
class TSPInstance {

public:
    TSPInstance(const char* file_name);
    
    TSPInstance(std::vector<std::array<float, 2>> vertices);

    virtual ~TSPInstance();

    inline std::vector<std::array<float, 2>> get_vertices() const { return vertices; }

    inline size_t get_vertex_count() const { return vertices.size(); }

    GraphMatrix get_neighborhood_matrix();
private:
    void load_from_file(const char* file_name);
    GraphMatrix matrix;
    std::vector<std::array<float, 2>> vertices;
};

#endif /* INSTANCE_HPP */