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

  /**
   * Inputs
   * - papa - node that needs to grow
   * - rx - x coord to grow toward
   * - ry - y coord to grow toward
   * 
   * returns ptr to Node that is STEP_SIZE toward rx, ry, with papa as parent
   */
  static shared_ptr<Node> growToward(shared_ptr<Node> papa, double rx, double ry, double stepSize) {
    double xdist = rx - papa->x;
    double ydist = ry - papa->y;

    double len = sqrt(xdist*xdist + ydist*ydist);

    double newX, newY;
    if(Constants::equals(len, 0)) {
      // could be more random, but ...
      newX = papa->x + stepSize;
      newY = papa->y + stepSize;
    } else {
      newX = papa->x + xdist/len*stepSize;
      newY = papa->y + ydist/len*stepSize;
    } 
    return make_shared<Node>(newX, newY, papa);
  }

  double distanceTo(double ox, double oy) const {
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
