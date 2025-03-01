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

  bool isInBounds() {
    if(x<0 || y<0 || x > Constants::WIDTH || y > Constants::HEIGHT) {
      return false;
    }
    return true;
  }

  void printMe() const {
    cout << x << " " << y << endl;;
  }

  cv::Point getCvPoint() const {
    return cv::Point(static_cast<int>(x*Constants::SCALE), static_cast<int>(y*Constants::SCALE));
  }
};

#endif
