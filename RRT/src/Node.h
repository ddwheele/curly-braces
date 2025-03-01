#ifndef NODE_H
#define NODE_H

#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Constants.h"

using namespace std;

struct Node {
  double x, y;
  shared_ptr<Node> parent;

  Node(double _x, double _y, shared_ptr<Node> _parent = nullptr) 
    : x(_x), y(_y), parent(_parent) {
  }

  double distanceTo(const double ox, const double oy) const {
    double dx = x - ox;
    double dy = y - oy;
    return sqrt( dx*dx + dy*dy );
  }

  double distanceTo(const Node& other) const {
    return distanceTo(other.x, other.y);
  }

  void printMe() const {
    cout << x << " " << y << endl;;
  }

  cv::Point getCvPoint() const {
    return cv::Point(static_cast<int>(x*Constants::SCALE), static_cast<int>(y*Constants::SCALE));
  }
};

#endif
