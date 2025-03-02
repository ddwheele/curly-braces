#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Constants.h"
#include "RrtNode.h"

using namespace std;

class Obstacle {
public:
  Obstacle(double x1, double y1, double x2, double y2);

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
