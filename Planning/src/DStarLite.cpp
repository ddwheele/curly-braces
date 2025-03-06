#include <iostream>
#include <limits>
#include "DStarLite.h"


DStarLite::DStarLite(vector<shared_ptr<DStarNode>> node) : drawMap(*this) {

}

// if a Node has changed
void RecalculateNode(shared_ptr<DStarNode> changed) {
	key_modifier += changed.computeHeuristic(start);

	for(auto it = neighbors.begin(); it != neighbors; ++it) {
		auto ney = *it;
		if(ney != start) {
			ney->setRhs(std::min(ney->getRhs(), changed->distanceTo(*ney)+ changed->getGn()));
		}
		UpdateVertex(ney);
	}
	UpdateVertex(changed);
	ComputeShortestPath();
}

void computeShortestPath() {
	int stepsLeft = maxSteps;
 	while(openSet.getSize() > 0 && 
 	((openSet.peek()->getKey() < start->getKey()) || (start->getRhs() > start->getGn()) )) {
		if(stepsLeft-- <=0 ) {
			cout << "Did not find a path in " << maxSteps<< " iterations. Aborting." << endl;
			break;
		}
		auto node = openSet.extractMin();
		Key oldKey = node->getKey();
		Key newKey = node->computeKey(key_modifier);
		if(oldKey < newKey) {
			openSet.insertValue(node);
		} else if(node->getGn() > node->getRhs()) {
			node->setGn(node->getRhs());
			for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
				auto ney = *it;
				if(ney != goal) {
					ney->setRhs(std::min(ney->getRhs(), node->distanceTo(*ney)+ node->getGn()));
				}
				UpdateVertex(ney);
			}

		} else {
			double oldGn = node->getGn();
			node->setGn(numeric_limits<double>::max());

			// go through neighbors
			for(auto it = neighbors.begin(); it != neighbors.end(); ++it) {
				auto ney = *it;
				double costThroughNeighbor = node->distanceTo(*ney) + oldGn;
				if(Utils::equals(ney->getRhs(), costThroughNeighbor)) {
					if(ney != goal) {
						ney->setRhs(numeric_limits<double>::max()); 
						// invalidates prev. calculations
					}

					for(auto it2 = ney->getNeighbors().begin(); it2 != ney->getNeighbors().end(); ++it2) {
						auto neyney = *it2;
						ney->setRhs(std::min(ney->getRhs(), ney->distanceTo(*neyney) + neyney->getGn()));
					}
				}
				UpdateVertex(ney);
			}
			// AND FOR node ITSELF - but is that not sort of recursive??
			if(Utils::equals(node->getRhs(), oldGn)) {
				if(node != goal) {
					node->setRhs(numeric_limits<double>::max()); 
					// invalidates prev. calculations
				}

				for(auto iter2 = node->getNeighbors().begin(); iter2 != node->getNeighbors().end(); ++iter2) {
					auto neyney = *iter2;
					node->setRhs(std::min(node->getRhs(), node->distanceTo(*neyney) + neyney->getGn()));
				}
			}
			UpdateVertex(node);
		}
  }
	start->setGn(start->getRhs());
	cout << "Shortest path computed in " + (maxIterations - stepsLeft) + " steps." << endl;
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
		nd->setG(numeric_limits<double>::max());
	}
	goal->setRHS(0);
	goal->computeHeuristic(start);
	goal->computeKey(key_modifier);
	openSet.insertValue(goal);
}

void DStarLite::findPath()  {
	cout << "findPath called" << endl;
}