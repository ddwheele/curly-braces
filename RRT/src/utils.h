#ifndef UTILS_H
#define UTILS_H

#include <memory>

using namespace std;

struct Node {
  double x, y;
  shared_ptr<Node> parent;

  Node(double _x, double _y, shared_ptr<Node> _parent = nullptr) 
  : x(_x), y(_y), parent(_parent) {

  }
};

struct Point {
    float x;
    float y;
};


#endif
