#include <limits>
#include "StarNode.h"
#include "Utils.h"

StarNode::StarNode(const string& _name, const double _x, const double _y) :
  Node(_x, _y), name(_name), rng(std::random_device{}()), dist(margin, Utils::WIDTH-margin)  {
  }

StarNode::StarNode(const string& _name) : 
  name(_name), rng(std::random_device{}()), dist(margin, Utils::WIDTH-margin) {
    // create random coordinates

    x = dist(rng);
    y = dist(rng);
    cout << "Creating StarNode " << name << " at " << x <<", " << y << endl;
  }

  double StarNode::computeHeuristic(const shared_ptr<StarNode>& goal) {
    // let's use Euclidean distance for heuristic
    double xdiff = goal->x - x;
    double ydiff = goal->y - y;
    hn = sqrt(xdiff*xdiff + ydiff*ydiff);
    return hn;
  }

  double StarNode::evaluate() const  {
    // f(n) = g(n) + h(n)
    return gn + hn;
  }

  bool StarNode::compareDistance(const StarNode& a, const StarNode& b) const {
    return distanceTo(a) < distanceTo(b);
  }

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
    auto res = neighbors.insert(n);
    return res.second; // returns true if insert was successful
  }

  unordered_set<shared_ptr<StarNode>> StarNode::getNeighbors() const {
    return neighbors;
  }

  void StarNode::printMe() const {
    cout <<name <<": ("<< x << ", " << y << "), gn=" << gn <<", hn=" << hn << endl;
  }

