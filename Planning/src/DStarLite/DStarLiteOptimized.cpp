#include <iostream>
#include <algorithm>
#include <limits>
#include "DStarLiteOptimized.h"
#include "DrawMapDStarLite.h"

DStarLiteOptimized::DStarLiteOptimized(const vector<shared_ptr<DStarNode>>& _nodes,
											const vector<vector<shared_ptr<DStarNode>>>& edges, 
											const vector<double>& weights,
											const shared_ptr<DStarNode>& _start,
											const shared_ptr<DStarNode>& _goal) 
											: AbstractDStarLite(_nodes, edges, weights, _start, _goal) {
}

// must have start and goal nodes defined
// all nodes must have calculated heuristic
void DStarLiteOptimized::initialize() {
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

void DStarLiteOptimized::updateVertex(const std::shared_ptr<DStarNode>& node) {
  // if in open set and inconsistent, update and put back in open set
	if(!node->gnEqualsRhs() && openSet.contains(node)) {
    openSet.deleteNode(node);
    node->computeKey(key_modifier);
    openSet.insertNode(node);
		node->setInOpenSet(true); // should already be, but just in case
  } else if(!node->gnEqualsRhs() && !openSet.contains(node)) {
    // if inconsistent and not in open set, put in open set
    node->computeKey(key_modifier);
    openSet.insertNode(node);
		node->setInOpenSet(true); 
  } else if(node->gnEqualsRhs && openSet.contains(node)) {
    // if consistent, remove from open set
    openSet.deleteNode(node);
		node->setInOpenSet(false);
  }
}

void DStarLiteOptimized::computeShortestPath() {
  while((openSet.peek()->getKey() < start->computeKey(key_modifier)) || (start->getRhs() > start->getGn())) {
    auto node = openSet.extractMin();
		node->setInOpenSet(false);
		if(PRINT_DEBUG) {
			cout << "Popping node from queue: " << *node << endl;
		}
    DStarNode::Key oldKey = node->getKey();
    DStarNode::Key newKey = node->computeKey(key_modifier); // Achtung! Node has updated its key

    // Case 1: The Key got bigger, throw it back and look for a smaller one
    if(oldKey < newKey) {
      // key got bigger, update the Node in open set
      openSet.insertNode(node);
      node->setInOpenSet(true);

    // Case 2: G > RHS, relax G down to Rhs
    } else if(node->getGn() > node->getRhs()) {
      // RHS is lower, relax G
      node->setGn(node->getRhs());
      openSet.deleteNode(node); // this is redundant, we popped it
      // go through all predecessors
	    // inform predecessors they may have better value now
			for(auto& [ney, wt] : cost[node]) {
        if(ney != goal) {
          ney->setRhs(min(ney->getRhs(), wt));
          updateVertex(ney);
        }
			}
      // Case 3: 
    } else {
      double gOld = node->getGn();
      node->setGn(numeric_limits<double>::max());
      // go through all predecessors
      // inform predecessors they may have better value now
			for(auto& [ney, wt] : cost[node]) {
        if(ney->getRhs() == (wt + gOld)) {
          if(ney != goal) {
            // ... fill in here line 27"
          }
        }
          ney->setRhs(min(ney->getRhs(), wt));
          updateVertex(ney);
        }
			}
    }

  }
}

void DStarLiteOptimized::findPathInteractive()  {
	
}

void DStarLiteOptimized::findPath()  {
  cout << "DStarLiteOptimized::findPath() not implemented. Please use DStarLiteOptimized::findPathInteractive()" << endl;
}

