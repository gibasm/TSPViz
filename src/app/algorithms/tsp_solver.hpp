#ifndef TSP_SOLVER_HPP
#define TSP_SOLVER_HPP

#include "../gfx/graph.hpp"
#include "../instance.hpp"

/**
 * @brief Abstract TSP solver class.
 */
class TSPSolver {
public:
    /**
     * @brief Construct a new TSPSolver object
     * 
     * @param instance symmetric tsp instance
     * @param graph visual representation of the graph
     */
    TSPSolver(TSPInstance& instance, Graph& graph);
    virtual ~TSPSolver();

    /**
     * @brief should solve the TSP while displaying the results
     * on the graph's visual representation
     */
    virtual void solve() = 0;
    
protected:
    Graph& graph;
    TSPInstance& instance;
};

#endif /* TSP_SOLVER_HPP */