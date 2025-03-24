#include <limits>
#include "StarNode.h"
#include "Utils.h"

StarNode::StarNode(const string& _name, const double _x, const double _y) :
  Node(_x, _y), name(_name), rng(std::random_device{}()), dist(margin, Utils::WIDTH-margin)  {
  }

// Create a StarNode with a name and random coordinates in [0, Utils::WIDTH]
StarNode::StarNode(const string& _name) : 
  name(_name), rng(std::random_device{}()), dist(margin, Utils::WIDTH-margin) {
    // create random coordinates

    x = dist(rng);
    y = dist(rng);
    cout << "Creating StarNode " << name << " at " << x <<", " << y << endl;
  }

  // return Euclidean distance to the given node
  double StarNode::computeHeuristic(const shared_ptr<StarNode>& goal) {
    // let's use Euclidean distance for heuristic
    double xdiff = goal->x - x;
    double ydiff = goal->y - y;
    hn = sqrt(xdiff*xdiff + ydiff*ydiff);
    return hn;
  }

  // return f = g + h for this node
  double StarNode::evaluate() const  {
    // f(n) = g(n) + h(n)
    return gn + hn;
  }

  // return true if a is closer to this node than b, otherwise return false
  bool StarNode::compareDistance(const StarNode& a, const StarNode& b) const {
    return distanceTo(a) < distanceTo(b);
  }

  // given a list of StarNodes, reorder them from closest to farthest from this node
  void StarNode::orderNeighbors(vector<shared_ptr<StarNode>>& others) const {
    std::sort(others.begin(), others.end(), [this](const shared_ptr<StarNode>& a, const shared_ptr<StarNode>& b) {
          return compareDistance(*a, *b);});
  }

  const string& StarNode::getName() const {
    return name;
  }

  double StarNode::getGn() const {
    return gn;
  }

  void StarNode::setGn(const double _gn) {
    gn = _gn;
  }

  void StarNode::setParent(const shared_ptr<StarNode> newParent) {
    parent = newParent;
  }

  shared_ptr<StarNode> StarNode::getParent() const {
    return parent;
  }

  bool StarNode::addNeighbor(const shared_ptr<StarNode> n) {
    auto [_, success] = neighbors.insert(n);
    return success; // returns true if insert was successful
  }

  unordered_set<shared_ptr<StarNode>> StarNode::getNeighbors() const {
    return neighbors;
  }

  void StarNode::printMe() const {
    cout <<name <<": ("<< x << ", " << y << "), gn=" << gn <<", hn=" << hn << endl;
  }

