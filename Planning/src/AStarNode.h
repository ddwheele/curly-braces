#ifndef ASTAR_NODE_H
#define ASTAR_NODE_H

using namespace std;

class AStarNode : public Node  {
public:
  string name;
  double hn; // h(n) = heuristic. Admissible -> never overestimate the actual path cost
  // An admissible heuristic never overestimates the actual cost to reach the goal.
  // A consistent heuristic satisfies the condition that the estimated cost from the current 
  // node to the goal node is always less than or equal to the estimated distance from any 
  // neighbouring vertex to the goal, plus the cost of reaching that neighbour.
  double gn; // g(n) = operating cost = how many units we moved from start node
  shared_ptr<AStarNode> parent = nullptr;

  AStarNode(string _name, double _x, double _y) : Node(_x, _y), name(_name) {
  };

    void computeHeuristic(shared_ptr<AStarNode> goal) {
    // let's use Euclidean distance for heuristic
    double xdiff = goal->_x - _x;
    double ydiff = goal->_y - _y;
    _hn = sqrt(xdiff*xdiff + ydiff*ydiff);
  }

  double evaluate() const  {
    // f(n) = g(n) + h(n)
    return _gn + _hn;
  }

};



#endif