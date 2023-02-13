# TSPViz - Travelling Salesperson Problem vizualizer


[![CI/Build](https://github.com/TheMadMike/TSPViz/actions/workflows/cmake.yml/badge.svg)](https://github.com/TheMadMike/TSPViz/actions/workflows/cmake.yml)


The app is meant as an educational, fun to watch vizualization of popular algorithms used to solve the Travelling Salesperson Problem: Genetic Algorithms, and algorithms using the Ant Colony Optimization (otherwise known as "ant algorithms").

![tspviz sample screenshot](https://github.com/TheMadMike/TSPViz/blob/main/screenshots/tspviz.png?raw=true)

# Usage:

1. Get/create a *.tsp file:


Sample symmetric TSP instances to test can be found on [Heidelberg University's website](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp/).


**Warning:** TSPViz supports only instances in [TSPLIB95 EUC_2D](http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/tsp95.pdf) format!


2. Create a ***config.ini*** file in the directory of your *.tsp file(s). 


Here's a sample solver config file's content (***config.ini***):

```ini
algorithm_type = GA
iterations = 30000
population_size = 100
crossover_method = OX
mutation_method = SWAP
p_mutation = 0.4
```

* GA - genetic algorithm

* p_mutation - probability of mutation


3. Run:


```
tspviz <instance>.tsp
```

or if you want to see the current best path cost in the terminal:

```
tpsviz <instance>.tsp -d
```

# Building & testing

## Dependencies:

* git
* CMake >= 3.15 (for GNU/Linux also Make)
* spdlog 1.x
* SDL 2.x
* C++ toolchain with C++17 support


## Steps (GNU/Linux):

0. Make sure you've got all of the [dependencies](#dependencies) installed on your system.

1. Open a terminal and type:
```
git clone <url to this repo> 
``` 

2. Go to the cloned repository's directory
and create a directory named ``build``

3. Type:
```
cmake ..
```

then:

```
make
```

4. [Run the app](#usage)

5. Test by typing:
```
ctest
```