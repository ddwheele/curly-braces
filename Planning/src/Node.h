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

  Node(double _x, double _y);

  double distanceTo(double ox, double oy) const;

  double distanceTo(const Node& other) const;

  virtual void printMe() const;
};

#endif
