#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

#include <limits>
#include "Node.h"
#include "Utils.h"


using namespace std;

class AStarNode : public Node  {
public:
  AStarNode(string _name, double _x, double _y) : Node(_x, _y), name(_name) {
    // gn is a double, but using float_max so it doesn't overflow if we add something to it
    gn = numeric_limits<float>::max();
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

  const string& getName() const {
    return name;
  }

  double getGn() const {
    return gn;
  }

  void setGn(double _gn) {
    gn = _gn;
  }

  void setParent(shared_ptr<AStarNode> newParent) {
    parent = newParent;
  }

  const shared_ptr<AStarNode>& getParent() {
    return parent;
  }

  void printMe() const override {
    cout <<name <<": ("<< x << ", " << y << "), gn=" << Utils::infString(gn) <<", hn=" << hn << ", total=" << Utils::infString(evaluate()) << endl;
  }

private:
  string name;
  double hn; // h(n) = heuristic. Admissible -> never overestimate the actual path cost
  // An admissible heuristic never overestimates the actual cost to reach the goal.
  // A consistent heuristic satisfies the condition that the estimated cost from the current 
  // node to the goal node is always less than or equal to the estimated distance from any 
  // neighboring vertex to the goal, plus the cost of reaching that neighbor.
  double gn; // g(n) = operating cost = how many units we moved from start node
  shared_ptr<AStarNode> parent = nullptr;

};



#endif