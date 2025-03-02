#ifndef NODE_H
#define NODE_H

#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Constants.h"

using namespace std;

class Node {
public:
  double x, y;

  Node(double _x, double _y);

  double distanceTo(double ox, double oy) const;

  double distanceTo(const Node& other) const;

  void printMe() const;

  cv::Point getCvPoint() const;
};

#endif
