#include "Node.h"

using namespace std;

Node::Node(double _x, double _y) 
  : x(_x), y(_y) {
}

double Node::distanceTo(double ox, double oy) const {
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

cv::Point Node::getCvPoint() const {
  return cv::Point(static_cast<int>(x*Constants::SCALE), static_cast<int>(y*Constants::SCALE));
}

