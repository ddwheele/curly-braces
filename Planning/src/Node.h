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
  shared_ptr<Node> parent;

  Node(double _x, double _y, shared_ptr<Node> _parent = nullptr);

  /**
   * Inputs
   * - papa - node that needs to grow
   * - rx - x coord to grow toward
   * - ry - y coord to grow toward
   * 
   * returns ptr to Node that is STEP_SIZE toward rx, ry, with papa as parent
   */
  static shared_ptr<Node> growToward(shared_ptr<Node> papa, double rx, double ry, double stepSize);

  double distanceTo(double ox, double oy) const;

  double distanceTo(const Node& other) const;

  void printMe() const;

  cv::Point getCvPoint() const;
};

#endif
