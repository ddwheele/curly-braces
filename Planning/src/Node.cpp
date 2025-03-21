#include "Node.h"
#include "Utils.h"

using namespace std;

Node::Node(const double _x, const double _y) 
  : x(_x), y(_y) {
}

double Node::distanceTo(const double ox, const double oy) const {
  double dx = x - ox;
  double dy = y - oy;
  return sqrt( dx*dx + dy*dy );
}

double Node::distanceTo(const Node& other) const {
  return distanceTo(other.x, other.y);
}

void Node::printMe() const {
  cout << x << " " << y << endl;
}


