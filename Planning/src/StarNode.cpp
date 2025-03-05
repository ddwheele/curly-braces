#include <limits>
#include "StarNode.h"
#include "Utils.h"

StarNode::StarNode(string _name, double _x, double _y) :
  Node(_x, _y), name(_name), rng(std::random_device{}()), dist(1, Utils::WIDTH-1)  {
  }

StarNode::StarNode(string _name) : 
  name(_name), rng(std::random_device{}()), dist(1, Utils::WIDTH-1) {
    // create random coordinates

    x = dist(rng);
    y = dist(rng);
    cout << "Creating StarNode " << name << " at " << x <<", " << y << endl;
  }

  void StarNode::computeHeuristic(shared_ptr<StarNode> goal) {
    // let's use Euclidean distance for heuristic
    double xdiff = goal->x - x;
    double ydiff = goal->y - y;
    hn = sqrt(xdiff*xdiff + ydiff*ydiff);
  }

  double StarNode::evaluate() const  {
    // f(n) = g(n) + h(n)
    return gn + hn;
  }

  string StarNode::getName() const {
    return name;
  }

  double StarNode::getGn() const {
    return gn;
  }

  void StarNode::setGn(double _gn) {
    gn = _gn;
  }

  void StarNode::setParent(shared_ptr<StarNode> newParent) {
    parent = newParent;
  }

  shared_ptr<StarNode> StarNode::getParent() const {
    return parent;
  }

  bool StarNode::addNeighbor(shared_ptr<StarNode> n) {
    auto res = neighbors.insert(n);
    return res.second; // returns true if insert was successful
  }

  unordered_set<shared_ptr<StarNode>> StarNode::getNeighbors() const {
    return neighbors;
  }

  void StarNode::printMe() const {
    cout <<name <<": ("<< x << ", " << y << "), gn=" << gn <<", hn=" << hn << endl;
  }

