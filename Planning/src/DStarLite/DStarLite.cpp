#include <iostream>
#include <algorithm>
#include <limits>
#include "DStarLite.h"
#include "DrawMapDStarLite.h"

// call base class to create adjacency matrix (ie cost map) and compute heuristics
DStarLite::DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) 
											: AbstractDStarLite(_nodes, edges, weights, _start, _goal) {
}

// make sure RHS points to the best neighbor; if inconsistent, put on open queue
void DStarLite::updateVertex(const std::shared_ptr<DStarNode>& node) {
	if(PRINT_DEBUG) {
		cout << "Updating Vertex: " << *node << endl;
	}
	if(node != goal) {
		// set rhs to minimum of cost through neighbors
		double best = numeric_limits<double>::max();
		for(auto& [ney, cst] : cost[node]) {
			if(PRINT_DEBUG) {
				cout<<"\tneighbor = " << ney->getName() << ", cost = " << cst << ", g = " << Utils::infString(ney->getGn()) << endl;
			}
			best = std::min(best, cst + ney->getGn());
		}
		if(PRINT_DEBUG) {
			cout << "\tsetting to RHS of " << node->getName() << " to " << Utils::infString(best) << endl;
		}
		node->setRhs(best);
	}
	if(openSet.contains(node)) {
		openSet.deleteNode(node);
		node->setInOpenSet(false);
	}
	if(!node->gnEqualsRhs()) {
		if(PRINT_DEBUG) {
			cout << "\tInconsistent, putting on " << node->getName() <<" on open set" << endl;
		}
		node->computeKey(key_modifier);
		openSet.insertNode(node);
		node->setInOpenSet(true);
	}
}

// process open set until Start is consistent, and all nodes with smaller keys than Start are processed
void DStarLite::computeShortestPath() {
	int stepsLeft = maxSteps;

	// process open set until Start is consistent, and all nodes with smaller keys than Start are processed
 	while(openSet.getSize() > 0 && 
 	((openSet.peek()->getKey() < start->computeKey(key_modifier)) || !Utils::equals(start->getRhs(), start->getGn()) )) {
		if(stepsLeft-- <=0 ) {
			cout << "Did not find a path in " << maxSteps<< " iterations. Aborting." << endl;
			break;
		}
		// get the node with lowest expected path cost, break ties with steps to here (g)
		auto node = openSet.extractMin();
		node->setInOpenSet(false);
		if(PRINT_DEBUG) {
			cout << "------------------------------------" << endl;
			cout << "^^^^^^ Popping node @@ " << *node << endl;
		}
		DStarNode::Key oldKey = node->getKey();
		// Case 1: The Key got bigger, throw it back and look for a smaller one
		if(node->computeKey(key_modifier) > oldKey ) {
			if(PRINT_DEBUG) {
				cout << "\t-key got bigger, put back in openSet" << endl;
			}
			openSet.insertNode(node);
			node->setInOpenSet(true);

		// Case 2: G > RHS, relax G down to Rhs and tell all neighbors
		} else if(node->getGn() > node->getRhs()) {
			if(PRINT_DEBUG) {
				cout << "\tG > RHS, relaxing G and calling the neighbors" << endl;
			}
			// relax g
			node->setGn(node->getRhs());

			// inform predecessors they may have better value now
			for(auto& [ney, _] : cost[node]) {
				updateVertex(ney);
			}
		// Case 3: G <= Rhs, set G=inf and propagate to neighbors
		} else {
			if(PRINT_DEBUG) {
				cout << "\tG <= RHS, blowing up G and calling the neighbors" << endl;
			}
			double oldGn = node->getGn();
			// give up and reset g to inf
			node->setGn(numeric_limits<double>::max());

			// go through predecessors
			for(auto& [ney, _] : cost[node]) {
				updateVertex(ney);
			}
			updateVertex(node);

		}
		if(PRINT_DEBUG) {
			drawMapAndWait();
		}
  }
	cout << "OpenSet size=" <<openSet.getSize() << endl;
	if(openSet.getSize() > 0) {
		cout << "Head of OpenSet = " << *openSet.peek() << endl;
		DStarNode::Key startKey = start->computeKey(key_modifier);
		cout << "Start Key = " << startKey.toString() << endl;
	}

	if(PRINT_DEBUG) {
		cout << "FINISHED computeShortestPath." << endl;
		cout << "Shortest path computed in " << (maxSteps - stepsLeft) << " steps." << endl;
		printState();
	}
}

// turn a node into an obstacle (add weight to each edge)
void DStarLite::placeNamedObstacle(const string& obsName, const double weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			currentObstacles.insert(nd);
			updateEdgesTo(nd, weight);
		}
	}
}

// make a node not an obstacle anymore (subtract weight from each edge)
void DStarLite::removeNamedObstacle(const string& obsName, const double weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			currentObstacles.erase(nd);
			updateEdgesTo(nd, -weight);
		}
	}
}

// Add the given weight to all edges touching an obstacle
void DStarLite::updateEdgesTo(shared_ptr<DStarNode>& obstacle, const double weight) {
	if(!obstacle) {
		return;
	}
	if(PRINT_DEBUG) {
		cout << "ooooooooooooooooooooooooooooooo " << weight << endl;
		cout << "OBSTACLE AT NODE " << obstacle->getName() << endl;
	}
	for(auto& [ney, cst] : cost[obstacle]) {
		cost[obstacle][ney] += weight;
		cost[ney][obstacle] += weight;
		updateVertex(ney);
		if(PRINT_DEBUG) {
			drawMapAndWait();
		}
	}
	updateVertex(obstacle);
	if(PRINT_DEBUG) {
			drawMapAndWait();
	}
}

void DStarLite::setTimedObstacles(vector<shared_ptr<DStarNode>>& _timedObstacles) {
	timedObstacles = _timedObstacles;
}

// must have start and goal nodes defined before calling
// all nodes must have calculated heuristic before calling
void DStarLite::initialize() {
	openSet.clear();
	key_modifier = 0;
	for(auto nd : nodes) {
		nd->setRhs(numeric_limits<double>::max());
		nd->setGn(numeric_limits<double>::max());
	}
	goal->setRhs(0);
	goal->computeHeuristic(start);
	goal->computeKey(key_modifier);
	openSet.insertNode(goal);
	goal->setInOpenSet(true);
}

// call this to run D* Lite and specify obstacles interactively
void DStarLite::findPathInteractive()  {
	drawMap();
  cout << "\n%%%%%%%%%%%% STARTING AT NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;
	lastStart = start;
	initialize();
	cout << "DONE INITIALIZING" << endl;
	computeShortestPath();

	while(start != goal) {
		if(Utils::equals(start->getGn(), numeric_limits<double>::max())) {
			cout << "No path found" << endl;
			return;
		}

		// update obstacles and recompute shortest path
		doObstacleUpdates();
		
		double best = numeric_limits<double>::max();
		// find the neighbor with lowest g + cost to start
		shared_ptr<DStarNode> nextNode;
		for(auto& [ney, cst] : cost[start]) {
			double est = ney->getGn() + cst;
			if(est < best) {
				best = est;
				nextNode = ney;
			}
		}
	
		// move to the best neighbor
		cout << "\n%%%%%%%%%%%% ADVANCE TO NODE " << nextNode->getName() << " %%%%%%%%%%%%\n" << endl;
		start = nextNode;
		drawMap();
	}
  cout << "\n%%%%%%%%%%%%%%%% AT GOAL " << start->getName() << " %%%%%%%%%%%%%%%%\n" << endl;
}

// handles a single moving obstacle, specified in timedObstacles
// call this to run D* Lite if you have specified a list of timed obstacles
void DStarLite::findPath()  {
	// THIS IS PROBABLY NOT THE FUNCTION YOU WANT
  cout << "\n%%%%%%%%%%%% STARTING AT NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;
	lastStart = start;
	initialize();

	computeShortestPath();
	int obstacleTime = 0;
	while(start != goal) {
		if(Utils::equals(start->getGn(), numeric_limits<double>::max())) {
			cout << "No path found" << endl;
			return;
		}
		double best = numeric_limits<double>::max();
		// find the neighbor with lowest g + cost to start
		shared_ptr<DStarNode> nextNode;
		for(auto& [ney, cst] : cost[start]) {
			double est = ney->getGn() + cst;
			if(est < best) {
				best = est;
				nextNode = ney;
			}
		}

		// move to the best neighbor
		cout << "\n%%%%%%%%%%%% ADVANCE TO NODE " << nextNode->getName() << " %%%%%%%%%%%%\n" << endl;
		start = nextNode;

		// did anything change?
		applyTimedObstacles(obstacleTime);
	}
  cout << "\n%%%%%%%%%%%%%%%% AT GOAL " << start->getName() << " %%%%%%%%%%%%%%%%\n" << endl;
}

// findPath() calls this to apply the specified timed obstacles to the graph
void DStarLite::applyTimedObstacles(int &obstacleTime) {
	if(!timedObstacles.empty() && timedObstacles[obstacleTime]) {
		// increment km by h(start, lastStart)
		key_modifier += start->distanceTo(*lastStart);
		lastStart = start;
		// for all edge changes
		// update edge cost in cost
		updateEdgesTo(timedObstacles[obstacleTime], 1000);
		if(obstacleTime > 0) {
			updateEdgesTo(timedObstacles[obstacleTime-1], -1000);
		}
		obstacleTime++;
		// (vertices were updated inside the Obstacle functions)
		computeShortestPath();
	}
}