#include "Node.h"
#include "Utils.h"

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

bool Node::compareDistance(const Node& a, const Node& b) const {
  return distanceTo(a) < distanceTo(b);
}

void Node::orderNeighbors(vector<shared_ptr<Node>>& others) const {
  std::sort(others.begin(), others.end(), [this](const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
        return compareDistance(*a, *b);});
}

void Node::printMe() const {
  cout << x << " " << y << endl;
}

cv::Point Node::getCvPoint() const {
  return cv::Point(static_cast<int>(x*Utils::SCALE), static_cast<int>(y*Utils::SCALE));
}

