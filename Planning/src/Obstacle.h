#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "RRT/RrtNode.h"

using namespace std;

class Obstacle {
public:
  Obstacle(const double x1, const double y1, const double x2, const double y2);

  // checks the line between a Node and its parent
  bool intersects(const RrtNode& n) const;

  void printMe() const;

  cv::Point getMinCvPoint() const;
  cv::Point getMaxCvPoint() const;
  bool pointIsInside(const double x, const double y) const;

private:
  double minx, miny, maxx, maxy; // two corners of the obstacle
};

#endif
