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
		cout << "Updating " << *node << endl;
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
			cout << "Popping node from queue: " << *node << endl;
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
//	start->setGn(start->getRhs());
	if(PRINT_DEBUG) {
		cout << "Shortest path computed in " << (maxSteps - stepsLeft) << " steps." << endl;
		printState();
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
		if(Utils::equals(start->getGn(), numeric_limits<double>::max())) {
			cout << "No path found" << endl;
			return;
		}
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

		// move to nextNode
		cout << "\n%%%%%%%%%%%% ADVANCE TO NODE " << nextNode->getName() << " %%%%%%%%%%%%\n" << endl;
		start = nextNode;
		drawMap();
	}
  cout << "\n%%%%%%%%%%%%%%%% AT GOAL " << start->getName() << " %%%%%%%%%%%%%%%%\n" << endl;
}

void DStarLite::findPath()  {
	// handles single moving obstacle, specified in timedObstacles
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
		placeObstacle(timedObstacles[obstacleTime]);
		if(obstacleTime > 0) {
			removeObstacle(timedObstacles[obstacleTime-1]);
		}
		obstacleTime++;
		// (vertices were updated inside the Obstacle functions)
		computeShortestPath();
	}
}



