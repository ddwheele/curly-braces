#include <limits>
#include "StarNode.h"

StarNode::StarNode(string _name, double _x, double _y) :  Node(_x, _y), name(_name) {
    gn = MAX_DOUBLE;
    rhs = MAX_DOUBLE;
  };

StarNode::StarNode(string _name) :  name(_name) {
    // create random coordinates
    std::srand(std::time(0));
    x = std::rand() % static_cast<int>(Utils::WIDTH);
    y = std::rand() % static_cast<int>(Utils::HEIGHT);

    gn = MAX_DOUBLE;
    rhs = MAX_DOUBLE;
  };

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

  bool StarNode::gnEqualsRhs() const {
    return Utils::equals(gn, rhs);
  }

  double StarNode::getGn() const {
    return gn;
  }

  void StarNode::setGn(double _gn) {
    gn = _gn;
  }

  double StarNode::getRhs() const {
    return rhs;
  }

  void StarNode::setRhs(double _gn) {
    rhs = _rhs;
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

