#include <iostream>
#include <limits>
#include "DStarLite.h"


DStarLite::DStarLite(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) : nodes(_nodes), start(_start), goal(_goal) {
	if(edges.size() != weights.size()) {
		throw std::invalid_argument("weights and edges must be equal length");
	}
	for(int i=0; i<edges.size(); i++) {
		cost[edges[i][0]][edges[i][1]] = weights[i];
		cost[edges[i][1]][edges[i][0]] = weights[i];
	}
	printState();
}

// if a Node has changed
void DStarLite::recalculateNode(shared_ptr<DStarNode>& changed) {
	// key_modifier += changed->computeHeuristic(start);

	// for(auto ney : changed->getDStarNeighbors()) {
	// 	if(ney != start) {
	// 		ney->setRhs(std::min(ney->getRhs(), changed->distanceTo(*ney)+ changed->getGn()));
	// 	}
	// 	updateVertex(ney);
	// }
	// updateVertex(changed);
	// computeShortestPath();
}

void DStarLite::updateVertex(const std::shared_ptr<DStarNode>& node) {
	if(!node->gnEqualsRhs() && openSet.contains(node)) {
		openSet.deleteNode(node);
		node->computeKey(key_modifier);
		openSet.insertNode(node);
	} 
	else if(!node->gnEqualsRhs() && !openSet.contains(node)) {
		node->computeKey(key_modifier);
		openSet.insertNode(node);
	}
	else if(node->gnEqualsRhs() && openSet.contains(node)) {
		openSet.deleteNode(node);
	}
}

void DStarLite::computeShortestPath() {
	int stepsLeft = maxSteps;
 	while(openSet.getSize() > 0 && 
 	((openSet.peek()->getKey() < start->computeKey(key_modifier)) || (start->getRhs() > start->getGn()) )) {
		if(stepsLeft-- <=0 ) {
			cout << "Did not find a path in " << maxSteps<< " iterations. Aborting." << endl;
			break;
		}
		auto node = openSet.extractMin();
		DStarNode::Key oldKey = node->getKey();
		DStarNode::Key newKey = node->computeKey(key_modifier);

		if(oldKey < newKey) {
			openSet.insertNode(node);
		} else if(node->getGn() > node->getRhs()) {
			// relax g
			node->setGn(node->getRhs());

			// inform predecessors they may have better value now
			for(auto ney : node->getPredecessors()) {
				if(ney != goal) {
					ney->setRhs(std::min(ney->getRhs(), cost[node][ney] + node->getGn()));
				}
				updateVertex(ney);
			}
		} else {
			double oldGn = node->getGn();
			// give up and reset g to inf
			node->setGn(numeric_limits<double>::max());

			// go through predecessors
			for(auto ney : node->getPredecessors()) {
				double costThroughNeighbor = cost[node][ney] + oldGn;
				if(Utils::equals(ney->getRhs(), costThroughNeighbor)) {
					if(ney != goal) {
						ney->setRhs(numeric_limits<double>::max()); 
						// invalidates prev. calculations
					}

					for(auto neyney : ney->getDStarNeighbors()) {
						ney->setRhs(std::min(ney->getRhs(), cost[ney][neyney] + neyney->getGn()));
					}
				}
				updateVertex(ney);
			}
			// AND FOR node ITSELF - but is that not sort of recursive??
			if(Utils::equals(node->getRhs(), oldGn)) {
				if(node != goal) {
					node->setRhs(numeric_limits<double>::max()); 
					// invalidates prev. calculations
				}

				for(auto neyney : node->getDStarNeighbors()) {
					node->setRhs(std::min(node->getRhs(), cost[node][neyney] + neyney->getGn()));
				}
			}
			updateVertex(node);
		}
  }
	start->setGn(start->getRhs());
	cout << "Shortest path computed in " << (maxSteps - stepsLeft) << " steps." << endl;
}

//must have start and goal nodes defined
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
	cout << "findPath called" << endl;
}

void DStarLite::printState() const {
	cout << "=====  D*Lite  =====" << endl;
	for(auto n : nodes) {
		cout << *n << endl;
	}
}