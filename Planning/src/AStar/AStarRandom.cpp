#include "AStarRandom.h"


AStarRandom::AStarRandom(vector<shared_ptr<StarNode>> nodes) : nodes(nodes), drawMap(*this) {
	for(const auto& n : nodes) {
		if(n->getName() == "Start") {
			start = n;
		} else if(n->getName() == "Goal") {
			goal = n;
		}
	}

  for(auto node : nodes) {
    for(auto neigh : node->getNeighbors()) {
      double dist = node->distanceTo(*neigh);
      adj[node].push_back({neigh, dist});
      // make all edges bi-directional to start
      adj[neigh].push_back({node, dist});
    }
  }
}

void AStarRandom::findPath(){

  if(!start || !goal) {
  	cout << "No nodes named Start or Goal found, aborting" << endl;
  	return;
  }
  cout << "Start = ";
  start->printMe();
   cout << "Goal = ";
  goal->printMe();

  set<shared_ptr<StarNode>> closed;

  for(auto n : nodes) {
    n->computeHeuristic(goal);
  }
  // Using lambda to compare elements.
  auto cmp = [](shared_ptr<StarNode> left, shared_ptr<StarNode> right) { 
    return left->evaluate() > right->evaluate(); }; // want the smallest values popped first

  std::priority_queue<shared_ptr<StarNode>,vector<shared_ptr<StarNode>>,decltype(cmp)> open(cmp);
  open.push(start);
  while(!open.empty()) {
    auto nd1 = open.top();
    open.pop();
    //cout << "Considering ";
    //nd1->printMe();

    if(nd1 == goal) {
      cout <<"Final Path Length = " << nd1->getGn() << endl;
      break;
    }
    closed.insert(nd1);
    auto neigh = adj[nd1];
    for(auto& pr: neigh) {
      auto nd2 = pr.first;
      double w = pr.second;
      if(closed.count(nd2)) {
        continue;
      }
      nd2->setGn(nd1->getGn() + w); // cost to neighbor = cost to old node + edge length
      nd2->setParent(nd1);
     // cout << "Adding " << nd2->getName() << ": " << nd2->evaluate() << endl;;
      open.push(nd2);
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

map<shared_ptr<StarNode>, vector<pair<shared_ptr<StarNode>,double>>> AStarRandom::getAdjacencyMatrix() const {
			return adj;
}

	shared_ptr<StarNode> AStarRandom::getGoal() const {
		return goal;
	}

