#include <iostream>
#include <algorithm>
#include <limits>
#include "DStarLite.h"
#include "DrawMapDStarLite.h"

DStarLite::DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) : nodes(_nodes), start(_start), goal(_goal),
											 dStarDrawMap(make_unique<DrawMapDStarLite>(*this)) {
  
	if(!edges.empty()) {
		//cout << "There are edges, I want to ingest them" << endl;
		if(edges.size() != weights.size()) {
			throw std::invalid_argument("weights and edges must be equal length");
		}
		for(int i=0; i<edges.size(); i++) {
			//cout << "Connecting " << edges[i][0]->getName() << " to " << edges[i][1]->getName() << endl;
			cost[edges[i][0]][edges[i][1]] = weights[i];
			cost[edges[i][1]][edges[i][0]] = weights[i];
		}
	} else {
		cout << "there are no edges" << endl;
	}
}

void DStarLite::placeObstacle(shared_ptr<DStarNode>& obstacle, int weight) {
	if(!obstacle) {
		return;
	}
	if(PRINT_DEBUG) {
		cout << "OBSTACLE AT NODE " << obstacle->getName() << endl;
	}
	for(auto& [ney, cst] : cost[obstacle]) {
		cost[obstacle][ney] += weight;
		cost[ney][obstacle] += weight;
		updateVertex(ney);
	}
	updateVertex(obstacle);
}

void DStarLite::removeObstacle(shared_ptr<DStarNode>& obstacle, int weight) {
	if(!obstacle) {
		return;
	}
	if(PRINT_DEBUG) {
		cout << "REMOVED OBSTACLE AT NODE " << obstacle->getName() << endl;
	}
	for(auto& [ney, cst] : cost[obstacle]) {
		cost[obstacle][ney] -= weight;
		cost[ney][obstacle] -= weight;
		updateVertex(ney);
	}
	updateVertex(obstacle);
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
	}
	if(!node->gnEqualsRhs()) {
		if(PRINT_DEBUG) {
			cout << "\tInconsistent, putting on " << node->getName() <<" on open set" << endl;
		}
		node->computeKey(key_modifier);
		openSet.insertNode(node);
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
		if(PRINT_DEBUG) {
			cout << "Examining " << *node << endl;
		}
		DStarNode::Key oldKey = node->getKey();
		if(node->computeKey(key_modifier) > oldKey ) {
			if(PRINT_DEBUG) {
				cout << "\t-key got bigger, put back in openSet" << endl;
			}
			openSet.insertNode(node);
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
  }
//	start->setGn(start->getRhs());
	if(PRINT_DEBUG) {
		cout << "Shortest path computed in " << (maxSteps - stepsLeft) << " steps." << endl;
	}
	if(PRINT_DEBUG) {
		printState();
	}
}

void DStarLite::setTimedObstacles(vector<shared_ptr<DStarNode>>& _timedObstacles) {
	timedObstacles = _timedObstacles;
}

// must have start and goal nodes defined
// all nodes must have calculated heuristic
// order. Note that, in an actual
// implementation, Initialize() only needs to initialize a vertex
// when it encounters it during the search and thus does not
// need to initialize all v
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
}

void DStarLite::findPath()  {
	// handles single moving obstacle, specified in timedObstacles
  cout << "\n%%%%%%%%%%%% STARTING AT NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;
	shared_ptr<DStarNode> lastStart = start;
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

		if(!timedObstacles.empty() && timedObstacles[obstacleTime]) {
			// increment km by h(start, lastStart)
			key_modifier += start->distanceTo(*lastStart);
			lastStart = start;
			// for all edge changes
			// update edge cost in cost
			placeObstacle(timedObstacles[obstacleTime]);
			if(obstacleTime >0) {
				removeObstacle(timedObstacles[obstacleTime-1]);
			}
			obstacleTime++;
			// (vertices were updated inside the Obstacle functions)
			computeShortestPath();
		}
	}
  cout << "\n%%%%%%%%%%%%%%%% AT GOAL " << start->getName() << " %%%%%%%%%%%%%%%%\n" << endl;
}

const vector<shared_ptr<DStarNode>>& DStarLite::getNodes() const {
	return nodes;
}

 const unordered_map<shared_ptr<DStarNode>, unordered_map<shared_ptr<DStarNode>,double>>& DStarLite::getCostMap() const {
 	return cost;
 }


void DStarLite::drawMap() const {
	dStarDrawMap->drawMap();
}

void DStarLite::printState() const {
	cout << "====================  D*Lite  ====================" << endl;
	for(auto n : nodes) {
		cout << *n << endl;
	}
	cout << "==================================================" << endl;
}
