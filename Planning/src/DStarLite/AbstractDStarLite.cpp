#include <iostream>
#include <algorithm>
#include <limits>
#include "AbstractDStarLite.h"
#include "DrawMapDStarLite.h"

// create adjacency matrix (ie cost map) and compute heuristics
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
			if(PRINT_DEBUG) {
				cout << edges[i][0]->getName() << " to " << edges[i][1]->getName() << " = " << weights[i] << endl;
			}
		}
	} else {
		cout << "there are no edges" << endl;
	}
	for(auto nd : nodes) {
		nd->computeHeuristic(goal);
	}
}

// Ask user for obstacle updates, apply them to graph, and recompute shortest path
void AbstractDStarLite::doObstacleUpdates() {
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
