#ifndef STAR_NODE_H
#define STAR_NODE_H

#include <cmath>
#include <limits>
#include <random>
#include <unordered_set>
#include "Node.h"

using namespace std;

class StarNode : public Node {
public:

  StarNode(const string& _name, const double _x, const double _y);
  StarNode(const string& _name);

  double computeHeuristic(const shared_ptr<StarNode>& goal);

  // return fn for A*
  double evaluate() const;

  const string& getName() const;

  double getGn() const;
  void setGn(const double _gn);

  void setParent(const shared_ptr<StarNode> newParent);
  shared_ptr<StarNode> getParent() const;

  bool addNeighbor(const shared_ptr<StarNode> n);
  unordered_set<shared_ptr<StarNode>> getNeighbors() const;

  static constexpr double MAX_DOUBLE = std::numeric_limits<double>::max();

  void printMe() const override;

  // returns the given nodes sorted from closest to farthest from this node
  void orderNeighbors(vector<shared_ptr<StarNode>>& others) const;

  bool compareDistance(const StarNode& a, const StarNode& b) const;

protected:
  string name;
  double hn; // h(n) = heuristic. Admissible -> never overestimate the actual path cost
  // An admissible heuristic never overestimates the actual cost to reach the goal.
  // A consistent heuristic satisfies the condition that the estimated cost from the current 
  // node to the goal node is always less than or equal to the estimated distance from any 
  // neighboring vertex to the goal, plus the cost of reaching that neighbor.
  double gn; // g(n) = operating cost = how many units we moved from end node

  shared_ptr<StarNode> parent = nullptr;
  unordered_set<shared_ptr<StarNode>> neighbors;

  std::mt19937 rng;  // Independent random generator for each instance
  std::uniform_int_distribution<int> dist;  // Define distribution

  static constexpr int margin = 5;

};



#endif