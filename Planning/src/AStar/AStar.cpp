#include "AStar.h"
#include "DrawMapAStar.h"


AStar::AStar(const vector<shared_ptr<AStarNode>>& nodes,
	const vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>>& edges, 
	const vector<double>& weights) : nodes(std::move(nodes)), drawMap(make_unique<DrawMapAStar>(*this)) {
  
	for(const auto& n : nodes) {
		if(n->getName() == "Start") {
			start = n;
      start->setGn(0);
		} else if(n->getName() == "Goal") {
			goal = n;
		}
	}

  for(int i=0; i<edges.size(); i++) {
    auto e = edges[i];
    auto e1 = e.first;
    auto e2 = e.second;
    auto w = weights[i];
    adj[e1].push_back({e2,w});
    adj[e2].push_back({e1,w});
    cout << e1->getName() <<" <--> " << e2->getName() << " = " << w << endl;
  }
}

void AStar::findPath(){
  if(!start || !goal) {
  	cout << "No nodes named Start or Goal found, aborting" << endl;
  	return;
  }

  for(auto n : nodes) {
    n->computeHeuristic(goal);
  }
  cout << "Start = ";
  start->printMe();
  cout << "Goal = ";
  goal->printMe();

  // Using lambda to compare elements.
  auto cmp = [](shared_ptr<AStarNode> left, shared_ptr<AStarNode> right) { 
    return left->evaluate() > right->evaluate(); }; // want the smallest values popped first

  std::priority_queue<shared_ptr<AStarNode>,vector<shared_ptr<AStarNode>>,decltype(cmp)> open(cmp);
  open.push(start);
 
  while(!open.empty()) {
    auto nd1 = open.top();
    open.pop();
    cout << "Considering ";
    nd1->printMe();

    if(nd1 == goal) {
      cout <<"Final Path Length = " << nd1->getGn() << endl;
      break;
    }
    auto neigh = adj[nd1];
    for(auto& pr: neigh) {
      auto nd2 = pr.first;
      double w = pr.second;
    
      // cost to neighbor = cost to old node + edge length
      double tentativeG = nd1->getGn() + w;
      if(tentativeG < nd2->getGn()) {
        nd2->setGn(tentativeG); 
        nd2->setParent(nd1);
        open.push(nd2);
      }
    }
  }

  shared_ptr<AStarNode> curr = goal;
  cout << "I found this path: " << endl;

  while(curr != nullptr) {
    cout << curr->getName() << "(" << curr->getGn() << ") -> ";
    curr = curr->getParent();
  }
  cout << endl;
  drawMap->drawMap();
  drawMap->drawFinalPath();
}

const map<shared_ptr<AStarNode>, vector<pair<shared_ptr<AStarNode>,double>>>& AStar::getAdjacencyMatrix() const {
		return adj;
}

const shared_ptr<AStarNode>& AStar::getGoal() const {
	return goal;
}

