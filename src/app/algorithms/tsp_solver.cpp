#include "tsp_solver.hpp"

TSPSolver::TSPSolver(TSPInstance& instance, Graph& graph)
:graph(graph), instance(instance){}

TSPSolver::~TSPSolver(){}