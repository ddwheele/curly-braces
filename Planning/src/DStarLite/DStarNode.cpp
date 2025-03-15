#include "DStarNode.h"
#include <limits>
#include <memory>


DStarNode::DStarNode(string _name, double _x, double _y) : StarNode(_name, _x, _y) {
  initGnRhs();
}

DStarNode::DStarNode(string _name) : StarNode(_name) {
  initGnRhs();
}

DStarNode::DStarNode(char _name, double _x, double _y) : StarNode(string(1,_name), _x, _y) {
  initGnRhs();
}

DStarNode::DStarNode(char _name) : StarNode(string(1,_name)) {
  initGnRhs();
}

void DStarNode::initGnRhs() {
  gn = numeric_limits<double>::max();
  rhs = numeric_limits<double>::max();
}

DStarNode::Key DStarNode::getKey() const {
  return key;
}

DStarNode::Key DStarNode::computeKey(double km) {
  key.update(gn, rhs, hn, km);
  return key;
}

bool DStarNode::gnEqualsRhs() const {
  return Utils::equals(gn, rhs);
}

double DStarNode::getRhs() const {
  return rhs;
}

void DStarNode::setRhs(double _rhs) {
  rhs = _rhs;
}

bool DStarNode::isInOpenSet() const {
  return inOpenSet;
}

void DStarNode::setInOpenSet(bool inSet) {
  inOpenSet = inSet;
}

bool DStarNode::operator<(const DStarNode& other) const {
  return this->getKey() < other.getKey();
}

bool DStarNode::operator>(const DStarNode& other) const {
  return this->getKey() > other.getKey();
}

bool DStarNode::addDStarNeighbor(shared_ptr<DStarNode> n) {
  auto res = neighbors.insert(n);
  return res.second; // returns true if insert was successful
}

// TODO implement for directed nodes
const vector<shared_ptr<DStarNode>>& DStarNode::getPredecessors() const {
  return dStarNeighbors;
}

// TODO implement for directed nodes
const vector<shared_ptr<DStarNode>>& DStarNode::getSuccessors() const {
  return dStarNeighbors;
}

const vector<shared_ptr<DStarNode>>& DStarNode::getDStarNeighbors() const {
  return dStarNeighbors;
}