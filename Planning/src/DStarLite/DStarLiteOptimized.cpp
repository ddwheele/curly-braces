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
  cout << "Initializing.."<<endl;
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

  cout << "Start = ";
  start->printMe();
  cout << "Goal = ";
  goal->printMe();
}

void DStarLiteOptimized::updateVertex(const std::shared_ptr<DStarNode>& node) {
  // if in open set and inconsistent, update and put back in open set
	if(!node->gnEqualsRhs() && openSet.contains(node)) {
    openSet.deleteNode(node);
    node->computeKey(key_modifier);
    openSet.insertNode(node);
    node->setInOpenSet(true); // should already be, but just in case
    if(DEBUG_LEVEL>2) {
      cout << "Updating " << node->getName() << " in openset" << endl;
    }
  } else if(!node->gnEqualsRhs() && !openSet.contains(node)) {
    // if inconsistent and not in open set, put in open set
    node->computeKey(key_modifier);
    openSet.insertNode(node);
		node->setInOpenSet(true);
    if(DEBUG_LEVEL>2) {
      cout << "Pushing " << node->getName() << " in openset" << endl;
    }  
  } else if(node->gnEqualsRhs() && openSet.contains(node)) {
    // if consistent, remove from open set
    openSet.deleteNode(node);
		node->setInOpenSet(false);
  }
}

void DStarLiteOptimized::computeShortestPath() {
  cout << "in ComputeShortestPath" << endl;
  while((openSet.peek()->getKey() < start->computeKey(key_modifier)) || (start->getRhs() > start->getGn())) {
    auto node = openSet.extractMin();
		node->setInOpenSet(false);
		if(DEBUG_LEVEL>1) {
			cout << "Popping node from queue: " << *node << endl;
		}
    DStarNode::Key oldKey = node->getKey();
    DStarNode::Key newKey = node->computeKey(key_modifier); // Achtung! Node has updated its key
    if(DEBUG_LEVEL>2) {
      cout << "Updated the Key" << endl;
    }
    // Case 1: The Key got bigger, throw it back and look for a smaller one
    if(oldKey < newKey) {
      if(DEBUG_LEVEL>2) {
				cout << "\t-key got bigger, put back in openSet" << endl;
			}
      // key got bigger, update the Node in open set
      openSet.insertNode(node);
      node->setInOpenSet(true);

    // Case 2: G > RHS, relax G down to Rhs
    } else if(node->getGn() > node->getRhs()) {
      if(DEBUG_LEVEL>2) {
				cout << "\tG > RHS, relaxing G and calling the neighbors" << endl;
			}
      // RHS is lower, relax G
      node->setGn(node->getRhs());

      // go through all predecessors
	    // inform predecessors they may have better value now
			for(auto& [ney, wt] : cost[node]) {
        if(DEBUG_LEVEL>2) {
          cout << "\tConsidering neighbor " << ney->getName() << endl;
        }
        if(ney != goal) {
          ney->setRhs(min(ney->getRhs(), wt+node->getGn()));
        }
        updateVertex(ney);
			}

      // Case 3: blow up G
    } else {
      if(DEBUG_LEVEL>2) {
        cout << "\tIn Case 3: blow up G" << endl;
      }
      double gOld = node->getGn();
      node->setGn(numeric_limits<double>::max());
      // go through all predecessors of node
			for(auto& [ney, wt] : cost[node]) {
        // if the neighbor was depending on node
        if(ney->getRhs() == (wt + gOld)) {
          if(ney != goal) {
            // update the neighbor to depend on the best other alternative
            double lowest = numeric_limits<double>::max();
            for(auto& [neyney, neywt] : cost[ney]) {
              lowest = min(lowest, neywt + neyney->getGn());
            }
            ney->setRhs(lowest);
          }
        }
        updateVertex(ney);  
			}
      // also process the node itself the same way
      if(node->getRhs() ==  gOld) {
        if(node != goal) {
          // update the neighbor to depend on the best other alternative
          double lowest = numeric_limits<double>::max();
          for(auto& [neyney, neywt] : cost[node]) {
            lowest = min(lowest, neywt + neyney->getGn());
          }
          node->setRhs(lowest);
        }
      }
      updateVertex(node);
    }
    if(DEBUG_LEVEL>2) {
      drawMapAndWait();
    }
  }
  if(DEBUG_LEVEL>1) {
		cout << "Shortest path computed." << endl;
		printState();
	}
}

// turn a node into an obstacle
void DStarLiteOptimized::placeNamedObstacle(const string& obsName, double weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			updateEdgesTo(nd, weight);
			currentObstacles.insert(nd);
		}
	}
}

// make a node not an obstacle anymore
void DStarLiteOptimized::removeNamedObstacle(const string& obsName, double weight) {
	for(auto nd : nodes) {
		if(nd->getName() == obsName) {
			updateEdgesTo(nd, -weight);
			currentObstacles.erase(nd);
		}
	}
}

void DStarLiteOptimized::updateEdgesTo(shared_ptr<DStarNode>& obstacle, double weight) {
	if(!obstacle) {
		return;
	}
	if(DEBUG_LEVEL>1) {
		cout << "OBSTACLE AT NODE " << obstacle->getName() << endl;
	}
	for(auto& [ney, cst] : cost[obstacle]) {
    double oldCost = cost[obstacle][ney];
		cost[obstacle][ney] += weight;
		cost[ney][obstacle] += weight;

    if(oldCost > cost[obstacle][ney]) {
      // do both ways bc edges are undirected
      if(obstacle != goal) {
        obstacle->setRhs(min(obstacle->getRhs(), cost[obstacle][ney] + ney->getGn()));
      }
      if(ney != goal) {
        ney->setRhs(min(ney->getRhs(), cost[ney][obstacle] + obstacle->getGn()));
      }
    } else {
       // do both ways bc edges are undirected
       // obstacle = u, ney = v
      if(obstacle->getRhs() == (oldCost + ney->getGn())) {
        if(obstacle != goal) {
          double lowest = numeric_limits<double>::max();
          for(auto& [ney2, ney2cost] : cost[obstacle]) {
            if((ney2cost + ney2->getGn()) < lowest) {
              lowest = ney2cost + ney2->getGn();
            }
          }
          obstacle->setRhs(lowest);
        }
      }
      // ney = u, obstacle = v
      if(ney->getRhs() == (oldCost + obstacle->getGn())) {
        if(ney != goal) {
          double lowest = numeric_limits<double>::max();
          for(auto& [neyney, neycost] : cost[ney]) {
            if((neycost + neyney->getGn()) < lowest) {
              lowest = neycost + neyney->getGn();
            }
          }
          ney->setRhs(lowest);
        }
      }
    }
		updateVertex(ney);
		if(DEBUG_LEVEL>2) {
			drawMapAndWait();
		}
	}
  updateVertex(obstacle);
}

// corresponds to Main in paper
void DStarLiteOptimized::findPath()  {
  cout << "\n%%%%%%%%%%%% STARTING AT NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;
  lastStart = start;
  initialize();
  computeShortestPath();
  drawMap();

  while(start != goal) {

	  if(Utils::equals(start->getRhs(), numeric_limits<double>::max())) {
			cout << "No path found" << endl;
			return;
		}

    // go through successors of start
		// find the neighbor with lowest g + cost to start
    double best = numeric_limits<double>::max();
		for(auto& [ney, wt] : cost[start]) {
			double est = ney->getGn() + wt;
			if(est < best) {
				best = est;
				start = ney;
			}
		}
    // move to nextNode
		cout << "\n%%%%%%%%%%%% ADVANCE TO NODE " << start->getName() << " %%%%%%%%%%%%\n" << endl;

    // did anything change? 
    doObstacleUpdates();
    drawMap();
  } 
}