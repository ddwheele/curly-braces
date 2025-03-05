#ifndef NODE_H
#define NODE_H

#include <memory>
#include <algorithm>
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

class Node {
public:
  double x, y;

  Node() {}

  Node(double _x, double _y);

  double distanceTo(double ox, double oy) const;

  double distanceTo(const Node& other) const;

  // returns the given nodes sorted from closest to farthest from this node
  void orderNeighbors(vector<shared_ptr<Node>>& others) const;

  virtual void printMe() const;

  cv::Point getCvPoint() const;

  bool compareDistance(const Node& a, const Node& b) const;
};

#endif
