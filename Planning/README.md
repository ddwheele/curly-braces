A project that contains implementations of various planning algorithms. Everything is in 2D. 
* A* 
	* runAStar reads in a graph from a yaml file and runs A* on it
	
	<img src="./AStar.png">
	
	* runAStarRandom generates random nodes in between a start and goal node, and runs A*
	
	<img src="./AStarRandom.png">

* RRT - Rapidly-Expanding Random Tree
	* runRRT reads in obstacles and a start and goal point from a yaml file and runs bi-directional RRT on it

	<img src="./RRT.png">

* D* Lite 
	* runDStarLite runs D* Lite on a hard-coded graph of 5 nodes, with a moving obstacle also hard-coded in

To build:

```
mkdir build
cd build
cmake ..
make
```

Then run one of the following programs:

```
./runRRT <params.yaml>
./testRRT # unit tests

```

