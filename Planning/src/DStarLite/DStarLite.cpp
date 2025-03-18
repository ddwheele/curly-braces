#include <iostream>
#include <algorithm>
#include <limits>
#include "DStarLite.h"
#include "DrawMapDStarLite.h"

DStarLite::DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) 
											: AbstractDStarLite(_nodes, edges, weights, _start, _goal) {
}

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

void DStarLite::computeShortestPath() {
	int stepsLeft = maxSteps;
 	while(openSet.getSize() > 0 && 
 	((openSet.peek()->getKey() < start->computeKey(key_modifier)) || !Utils::equals(start->getRhs(), start->getGn()) )) {
		if(stepsLeft-- <=0 ) {
			cout << "Did not find a path in " << maxSteps<< " iterations. Aborting." << endl;
			break;
		}
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

		// Case 2: G > RHS, relax G down to Rhs
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

// turn a node into an obstacle
void DStarLite::placeNamedObstacle(const string& obsName, double weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			updateEdgesTo(nd, weight);
			currentObstacles.insert(nd);
		}
	}
}

// make a node not an obstacle anymore
void DStarLite::removeNamedObstacle(const string& obsName, double weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			updateEdgesTo(nd, -weight);
			currentObstacles.erase(nd);
		}
	}
}

void DStarLite::updateEdgesTo(shared_ptr<DStarNode>& obstacle, double weight) {
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

// must have start and goal nodes defined
// all nodes must have calculated heuristic
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

void DStarLite::findPathInteractive()  {
	drawMap();
  cout << "\n%%%%%%%%%%%% STARTING AT NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;
	lastStart = start;
	initialize();
	cout << "DONE INITIALIZING" << endl;
	computeShortestPath();

	cout << "@@@@@@@@@@@@@@@@@@@@@ DONE COMPUTING SHORTEST PATH @@@@@@@@@@@@@@@@@@@@@" << endl;

	while(start != goal) {
		cout <<"- TOP OF WHILE LOOP IN findPathInteractive()" << endl;
		if(Utils::equals(start->getGn(), numeric_limits<double>::max())) {
			cout << "No path found" << endl;
			return;
		}
		cout <<"- there exists a path to start" << endl;
		doObstacleUpdates();
		cout << "=== finished updating for new obstacles ===" << endl;
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
		cout << "=== I found the best node to move to ===" << endl;
		// move to nextNode
		cout << "\n%%%%%%%%%%%% ADVANCE TO NODE " << nextNode->getName() << " %%%%%%%%%%%%\n" << endl;
		start = nextNode;
		drawMap();
	}
  cout << "\n%%%%%%%%%%%%%%%% AT GOAL " << start->getName() << " %%%%%%%%%%%%%%%%\n" << endl;
}

void DStarLite::findPath()  {
	// THIS IS PROBABLY NOT THE FUNCTION YOU WANT

	// handles single moving obstacle, specified in timedObstacles
  cout << "\n%%%%%%%%%%%% STARTING AT NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;
	lastStart = start;
	initialize();

	computeShortestPath();
	int obstacleTime = 0;
	while(start != goal) {
		cout <<"- TOP OF WHILE LOOP IN findPath()" << endl;
		if(Utils::equals(start->getGn(), numeric_limits<double>::max())) {
			cout << "No path found" << endl;
			return;
		}
		cout <<"- there exists a path to start" << endl;
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

		// move to nextNode
		cout << "\n%%%%%%%%%%%% ADVANCE TO NODE " << nextNode->getName() << " %%%%%%%%%%%%\n" << endl;
		start = nextNode;

		// did anything change?
		applyTimedObstacles(obstacleTime);
	}
  cout << "\n%%%%%%%%%%%%%%%% AT GOAL " << start->getName() << " %%%%%%%%%%%%%%%%\n" << endl;
}

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