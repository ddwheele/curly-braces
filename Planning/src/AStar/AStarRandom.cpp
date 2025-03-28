#include <limits>
#include "AStarRandom.h"

AStarRandom::AStarRandom(const vector<shared_ptr<StarNode>>& nodes) 
: nodes(std::move(nodes)), drawMap(*this) {

  // set all g to inf, except Start g = 0
	for(const auto& n : nodes) {
    n->setGn(numeric_limits<float>::max());
		if(n->getName() == "Start") {
			start = n;
      start->setGn(0);
		} else if(n->getName() == "Goal") {
			goal = n;
		}
	}

  // Create adjacency matrix. Graph is undirected
  for(auto node : nodes) {
    for(auto neigh : node->getNeighbors()) {
      double dist = node->distanceTo(*neigh);
      adj[node].push_back({neigh, dist});
      // make all edges bi-directional to start
      adj[neigh].push_back({node, dist});
    }
  }
}

// finds shortest path and displays it as OpenCV image
void AStarRandom::findPath(){

  if(!start || !goal) {
  	cout << "No nodes named Start or Goal found, aborting" << endl;
  	return;
  }
  cout << "Start = ";
  start->printMe();
   cout << "Goal = ";
  goal->printMe();

  // compute heuristic to goal
  for(auto n : nodes) {
    n->computeHeuristic(goal);
  }
  // Using lambda to compare elements.
  auto cmp = [](shared_ptr<StarNode> left, shared_ptr<StarNode> right) { 
    return left->evaluate() > right->evaluate(); }; // want the smallest values popped first

  std::priority_queue<shared_ptr<StarNode>,vector<shared_ptr<StarNode>>,decltype(cmp)> open(cmp);
  open.push(start);
   
  // f = cost to get here + heuristic = estimated total path cost to goal
  while(!open.empty()) {
    // pop node with lowest estimated cost
    auto nd1 = open.top();
    open.pop();

    if(nd1 == goal) {
      cout <<"Final Path Length = " << nd1->getGn() << endl;
      break;
    }
        // go through the neighbors of node nd1
    for(auto& [nd2, w]: adj[nd1]) {
      // cost to neighbor = cost to old node + edge length
      double tentativeG = nd1->getGn() + w;
       // if the cost to neighbor improves going through nd1
      if(tentativeG < nd2->getGn()) {
        // update the neighbor's g
        nd2->setGn(tentativeG); 
        nd2->setParent(nd1);
        // put it in the queue
        open.push(nd2);
      }
    }
  }

  shared_ptr<StarNode> curr = goal;
  cout << "I found this path: " << endl;

  while(curr != nullptr) {
    cout << curr->getName() << "(" << curr->getGn() << ") -> ";
    curr = curr->getParent();
  }
  cout << endl;
  drawMap.drawMap();
  drawMap.drawFinalPath();
}

const map<shared_ptr<StarNode>, vector<pair<shared_ptr<StarNode>,double>>>& AStarRandom::getAdjacencyMatrix() const {
			return adj;
}

const shared_ptr<StarNode>& AStarRandom::getGoal() const {
  return goal;
}

