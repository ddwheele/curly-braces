#include "DStarNode.h"

bool DStarNode::gnEqualsRhs() const {
  return Utils::equals(gn, rhs);
}
double DStarNode::getRhs() const {
  return rhs;
}

void DStarNode::setRhs(double _gn) {
  rhs = _rhs;
}