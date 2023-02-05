# TSPViz - Travelling Salesperson Problem vizualizer


[![CI/Build](https://github.com/TheMadMike/TSPViz/actions/workflows/cmake.yml/badge.svg)](https://github.com/TheMadMike/TSPViz/actions/workflows/cmake.yml)


The app is meant as an educational, fun to watch vizualization of popular algorithms used to solve the Travelling Salesperson Problem: Genetic Algorithms, and algorithms using the Ant Colony Optimization (otherwise known as "ant algorithms").

![tspviz sample screenshot](https://github.com/TheMadMike/TSPViz/blob/main/screenshots/tspviz.png?raw=true)

# Usage:

**Note:**
The application is still in the early stage of development, it lacks: algorithm implementations, test coverage, deployments and other additional CI/CD pipelines. The fully functional app should arrive in few weeks.

```
tspviz <instance>.tsp
```

**Warning:** TSPViz supports only instances in TSPLIB95 EUC_2D format!

# Building & testing

## Dependencies:

* git
* CMake >= 3.15 (for GNU/Linux also Make)
* spdlog 1.x
* SDL 2.x
* C++ toolchain with C++17 support


## Steps (GNU/Linux):

1. Open a terminal and type:
```
git clone <url to this repo> 
``` 

2. Go to the cloned repository's directory
and create a directory named ``build``

3. 