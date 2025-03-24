#include "AStar.h"
#include "DrawMapAStar.h"


AStar::AStar(const vector<shared_ptr<AStarNode>>& nodes,
	const vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>>& edges, 
	const vector<double>& weights) : nodes(std::move(nodes)), drawMap(make_unique<DrawMapAStar>(*this)) {
  
  // Find Start and Goal. Set Start g to 0
	for(const auto& n : nodes) {
		if(n->getName() == "Start") {
			start = n;
      start->setGn(0);
		} else if(n->getName() == "Goal") {
			goal = n;
		}
	}

  // create adjacency matrix, format src: {dst, wt}
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

// finds shortest path and displays it as OpenCV image
void AStar::findPath(){
  if(!start || !goal) {
  	cout << "No nodes named Start or Goal found, aborting" << endl;
  	return;
  }

  // compute heuristic to goal
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

  priority_queue<shared_ptr<AStarNode>,vector<shared_ptr<AStarNode>>,decltype(cmp)> open(cmp);
  open.push(start);
 
  // f = cost to get here + heuristic = estimated total path cost to goal
  while(!open.empty()) {
    // pop node with lowest estimated cost
    auto nd1 = open.top();
    open.pop();
    cout << "Considering ";
    nd1->printMe();

    // if it's the goal, we're done
    if(nd1 == goal) {
      cout <<"Final Path Length = " << nd1->getGn() << endl;
      break;
    }

    // go through the neighbors of node nd1
    for(auto& [nd2, w]: adj[nd1]) {
      // cost to neighbor = cost to nd + edge length
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

