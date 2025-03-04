#ifndef STAR_NODE_H
#define STAR_NODE_H

#include <cmath>
#include <unordered_set>
#include "Node.h"

using namespace std;

class StarNode : public Node  {
public:
  StarNode(string _name, double _xß, double _y) :  name(_name), x(_x), y(_y) {
  };

  StarNode(string _name) :  name(_name) {
    // create random coordinates
    std::srand(std::time(0));
    x = std::rand() % static_cast<int>(Utils::WIDTH);
    y = std::rand() % static_cast<int>(Utils::HEIGHT);
  };

  void computeHeuristic(shared_ptr<AStarNode> goal) {
    // let's use Euclidean distance for heuristic
    double xdiff = goal->x - x;
    double ydiff = goal->y - y;
    hn = sqrt(xdiff*xdiff + ydiff*ydiff);
  }

  double evaluate() const  {
    // f(n) = g(n) + h(n)
    return gn + hn;
  }

  string getName() const {
    return name;
  }

  double getGn() const {
    return gn;
  }

  void setGn(double _gn) {
    gn = _gn;
  }

  void setParent(shared_ptr<StarNode> newParent) {
    parent = newParent;
  }

  shared_ptr<StarNode> getParent() const {
    return parent;
  }

  bool addNeighbor(shared_ptr<StarNode> n) {
    auto res = neighbors.insert(n);
    return res.second; // returns true if insert was successful
  }

  unordered_set<shared_ptr<StarNode>> getNeighbors() const {
    return neighbors;
  }

  void printMe() const override {
    cout <<name <<": ("<< x << ", " << y << "), gn=" << gn <<", hn=" << hn << endl;
  }

private:
  string name;
  double hn; // h(n) = heuristic. Admissible -> never overestimate the actual path cost
  // An admissible heuristic never overestimates the actual cost to reach the goal.
  // A consistent heuristic satisfies the condition that the estimated cost from the current 
  // node to the goal node is always less than or equal to the estimated distance from any 
  // neighboring vertex to the goal, plus the cost of reaching that neighbor.
  double gn; // g(n) = operating cost = how many units we moved from end node
  shared_ptr<StarNode> parent = nullptr;
  unordered_set<shared_ptr<StarNode>> neighbors;

};



#endif