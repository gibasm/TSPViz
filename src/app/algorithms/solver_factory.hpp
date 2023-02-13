#ifndef SOLVER_FACTORY_HPP
#define SOLVER_FACTORY_HPP

#include <map>
#include "tsp_solver.hpp"

typedef std::map<std::string, std::string> Dictionary;

class TSPSolverFactory {
public:
    static std::unique_ptr<TSPSolver> create(
        TSPInstance& instance, 
        Graph& graph,
        const Dictionary& ini_contents
    );
private:
    static std::unique_ptr<TSPSolver> create_ga(
        TSPInstance& instance, Graph& graph,
        const Dictionary& ini
        );
};

#endif /* SOLVER_FACTORY_HPP */