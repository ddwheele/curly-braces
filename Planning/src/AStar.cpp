#include "AStar.h"

AStar::AStar(vector<shared_ptr<AStarNode>> nodes,
	vector<pair<shared_ptr<AStarNode>,shared_ptr<AStarNode>>> edges, 
	vector<double> weights) : PathPlanner(), nodes(nodes) {
	for(const auto& n : nodes) {
		if(n->getName() == "Start") {
			start = n;
		} else if(n->getName() == "Goal") {
			goal = n;
		}
	}
}

 void AStar::findPath(){
      if(!start || !goal) {
      	cout << "No nodes named Start or Goal found, aborting" << endl;
      	return;
      }

      set<shared_ptr<AStarNode>> closed;

      for(auto n : nodes) {
        n->computeHeuristic(goal);
      }
      // Using lambda to compare elements.
      auto cmp = [](shared_ptr<AStarNode> left, shared_ptr<AStarNode> right) { 
        return left->evaluate() > right->evaluate(); }; // want the smallest values popped first

      std::priority_queue<shared_ptr<AStarNode>,vector<shared_ptr<AStarNode>>,decltype(cmp)> open(cmp);
      open.push(start);
      while(!open.empty()) {
        auto nd1 = open.top();
        open.pop();
        cout << "Considering " << nd1->getName() << ": " << nd1->evaluate() << endl;
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
          cout << "Adding " << nd2->getName() << ": " << nd2->evaluate() << endl;;
          open.push(nd2);
        }
      }

      shared_ptr<AStarNode> curr = goal;
      cout << "I found this path: " << endl;
      while(curr != nullptr) {
        cout << curr->getName() << "(" << curr->getGn() << ") -> ";
        curr = curr->getParent();
      }
      cout << endl;
    }