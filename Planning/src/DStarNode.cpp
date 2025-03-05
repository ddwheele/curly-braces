#include "DStarNode.h"
#include <limits>

DStarNode::DStarNode(string _name, double _x, double _y) : StarNode(_name, _x, _y) {
  gn = numeric_limits<double>::max();
  rhs = numeric_limits<double>::max();
}

DStarNode::DStarNode(string _name) : StarNode(_name) {
  gn = numeric_limits<double>::max();
  rhs = numeric_limits<double>::max();
}

Key DStarNode::getKey() const {
  return key;
}

void DStarNode::computeKey(double km) {
  double k1 = min(gn, rhs) + hn + km;
  double k2 = min(gn, rhs);
  key.set(k1, k2);
}

bool DStarNode::gnEqualsRhs() const {
  return Utils::equals(gn, rhs);
}

double DStarNode::getRhs() const {
  return rhs;
}

void DStarNode::setRhs(double _gn) {
  rhs = _rhs;
}

bool DStarNode::operator<(const StarNode& other) const {
  return getKey() < other.getKey();
}

bool DStarNode::operator>(const StarNode& other) const {
  return getKey() > other.getKey();
}