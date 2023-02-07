#ifndef TSP_SOLVER_HPP
#define TSP_SOLVER_HPP

#include "../gfx/graph.hpp"
#include "../instance.hpp"

/**
 * @brief Abstract TSP solver class.
 */
class TSPSolver {
public:
    TSPSolver(TSPInstance& instance, Graph& graph);
    virtual ~TSPSolver();

    virtual void solve() = 0;
protected:
    Graph& graph;
    TSPInstance& instance;
};

#endif /* TSP_SOLVER_HPP */