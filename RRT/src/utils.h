#ifndef UTILS_H
#define UTILS_H

#include <memory>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
  double x, y;
  shared_ptr<Node> parent;

  Node(double _x, double _y, shared_ptr<Node> _parent = nullptr) 
  : x(_x), y(_y), parent(_parent) {
  }

  void printMe() {
    cout << x << " " << y << endl;;
  }
};

// Define a struct for an obstacle (defined by two opposite corners)
struct Obstacle {
  double minx, miny, maxx, maxy; // two corners of the obstacle

  Obstacle(double x1, double y1, double x2, double y2) {
    minx = min(x1, x2);
    maxx = max(x1, x2);
    miny = min(y1, y2);
    maxy = max(y1, y2);
  }

  void printMe() {
    cout << "Obstacle: ("<<minx<<","<<miny<<") to ("<<maxx<<","<<maxy<<")"<<endl;
  }

};

#endif
