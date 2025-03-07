#include <iostream>
#include <limits>
#include "DStarLite.h"


DStarLite::DStarLite(const vector<shared_ptr<DStarNode>>& node)  {
//: drawMap(*this)
}

// if a Node has changed
void DStarLite::recalculateNode(shared_ptr<DStarNode>& changed) {
	key_modifier += changed->computeHeuristic(start);

	for(auto ney : changed->getDStarNeighbors()) {
		if(ney != start) {
			ney->setRhs(std::min(ney->getRhs(), changed->distanceTo(*ney)+ changed->getGn()));
		}
		updateVertex(ney);
	}
	updateVertex(changed);
	computeShortestPath();
}

void DStarLite::computeShortestPath() {
	int stepsLeft = maxSteps;
 	while(openSet.getSize() > 0 && 
 	((openSet.peek()->getKey() < start->getKey()) || (start->getRhs() > start->getGn()) )) {
		if(stepsLeft-- <=0 ) {
			cout << "Did not find a path in " << maxSteps<< " iterations. Aborting." << endl;
			break;
		}
		auto node = openSet.extractMin();
		DStarNode::Key oldKey = node->getKey();
		DStarNode::Key newKey = node->computeKey(key_modifier);
		if(oldKey < newKey) {
			openSet.insertValue(node);
		} else if(node->getGn() > node->getRhs()) {
			node->setGn(node->getRhs());
			for(auto ney : node->getDStarNeighbors()) {
				if(ney != goal) {
					ney->setRhs(std::min(ney->getRhs(), node->distanceTo(*ney)+ node->getGn()));
				}
				updateVertex(ney);
			}
		} else {
			double oldGn = node->getGn();
			node->setGn(numeric_limits<double>::max());

			// go through neighbors
			for(auto ney : node->getDStarNeighbors()) {
				double costThroughNeighbor = node->distanceTo(*ney) + oldGn;
				if(Utils::equals(ney->getRhs(), costThroughNeighbor)) {
					if(ney != goal) {
						ney->setRhs(numeric_limits<double>::max()); 
						// invalidates prev. calculations
					}

					for(auto neyney : ney->getDStarNeighbors()) {
						ney->setRhs(std::min(ney->getRhs(), ney->distanceTo(*neyney) + neyney->getGn()));
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
					node->setRhs(std::min(node->getRhs(), node->distanceTo(*neyney) + neyney->getGn()));
				}
			}
			updateVertex(node);
		}
  }
	start->setGn(start->getRhs());
	cout << "Shortest path computed in " << (maxSteps - stepsLeft) << " steps." << endl;
}

void DStarLite::updateVertex(const std::shared_ptr<DStarNode>& node) {
	if(!node->gnEqualsRhs() && !openSet.contains(node)) {
		node->computeKey(key_modifier);
		openSet.insertValue(node);
	}
	else if(node->gnEqualsRhs() && openSet.contains(node)) {
		openSet.deleteValue(node);
	}
	else if(openSet.contains(node)) {
		openSet.deleteValue(node);
		node->computeKey(key_modifier);
		openSet.insertValue(node);
	}
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
	openSet.insertValue(goal);
}

void DStarLite::findPath()  {
	cout << "findPath called" << endl;
}