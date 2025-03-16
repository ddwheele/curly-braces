#include <iostream>
#include <algorithm>
#include <limits>
#include "AbstractDStarLite.h"
#include "DrawMapDStarLite.h"

AbstractDStarLite::AbstractDStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) 
											: nodes(_nodes), start(_start), goal(_goal),
											 dStarDrawMap(make_unique<DrawMapDStarLite>(*this)) {
  
	if(!edges.empty()) {
		if(edges.size() != weights.size()) {
			throw std::invalid_argument("weights and edges must be equal length");
		}
		for(int i=0; i<edges.size(); i++) {
			cost[edges[i][0]][edges[i][1]] = weights[i];
			cost[edges[i][1]][edges[i][0]] = weights[i];
		}
	} else {
		cout << "there are no edges" << endl;
	}
}

// turn a node into an obstacle
void AbstractDStarLite::placeNamedObstacle(const string& obsName, int weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			placeObstacle(nd);
			currentObstacles.insert(nd);
		}
	}
}

// make a node not an obstacle anymore
void AbstractDStarLite::removeNamedObstacle(const string& obsName, int weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			removeObstacle(nd);
			currentObstacles.erase(nd);
		}
	}
}

void AbstractDStarLite::placeObstacle(shared_ptr<DStarNode>& obstacle, int weight) {
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
		if(PRINT_DEBUG) {
			drawMapAndWait();
		}
		
	}
	updateVertex(obstacle);
	if(PRINT_DEBUG) {
			drawMapAndWait();
		}
}

void AbstractDStarLite
::removeObstacle(shared_ptr<DStarNode>& obstacle, int weight) {
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

void AbstractDStarLite::doObstacleUpdates() {
	// Ask user for obstacle updates
	std::string obstaclesToRemove;
	std::string obstaclesToPlace;
	
	std::cout << "Enter obstacles to place, or empty string: ";
	std::getline(std::cin, obstaclesToPlace);  // Reads the entire line into the string variable

	if(!currentObstacles.empty()) {
		std::cout << "Enter obstacles to remove, or empty string: ";
		std::getline(std::cin, obstaclesToRemove);  // Reads the entire line into the string variable
	}

	if(obstaclesToPlace.size() > 0 || obstaclesToRemove.size() > 0) {
		key_modifier += start->distanceTo(*lastStart);
		lastStart = start;

		for(char toPlace: obstaclesToPlace) {
			placeNamedObstacle(string(1,toPlace));
		}

		for(char toRemove: obstaclesToRemove) {
			removeNamedObstacle(string(1,toRemove));
		}

		computeShortestPath();
	}
}

const vector<shared_ptr<DStarNode>>& AbstractDStarLite::getNodes() const {
	return nodes;
}

const unordered_map<shared_ptr<DStarNode>, unordered_map<shared_ptr<DStarNode>,double>>& AbstractDStarLite::getCostMap() const {
	return cost;
}

const shared_ptr<DStarNode>& AbstractDStarLite::getStartNode() const {
	return start;
}

const unordered_set<shared_ptr<DStarNode>>& AbstractDStarLite::getCurrentObstacles() const {
	return currentObstacles;
}

const vector<shared_ptr<DStarNode>> AbstractDStarLite::getNodeNeighbors(const shared_ptr<DStarNode>&node ) const {
	vector<shared_ptr<DStarNode>> ret;
	for(auto& [neigh, _] : cost) {
		ret.push_back(neigh);
	}
	return ret;
}

void AbstractDStarLite::drawMap() const {
	dStarDrawMap->drawMap();
}

void AbstractDStarLite::drawMapAndWait() const {
	dStarDrawMap->drawMapAndWait();
}

void AbstractDStarLite::printState() const {
	cout << "====================  D*Lite  ====================" << endl;
	for(auto n : nodes) {
		cout << *n << endl;
	}
	cout << "==================================================" << endl;
}
