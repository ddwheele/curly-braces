#ifndef NODE_H
#define NODE_H

#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Node {
public:
  double x, y;

  Node() {}

  Node(const double _x, const double _y);

  double distanceTo(const double ox, const double oy) const;

  double distanceTo(const Node& other) const;

  virtual void printMe() const;
};

#endif
