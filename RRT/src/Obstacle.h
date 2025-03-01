#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Constants.h"
#include "Node.h"

using namespace std;

class Obstacle {
  double minx, miny, maxx, maxy; // two corners of the obstacle

public:
  Obstacle(double x1, double y1, double x2, double y2);

  bool intersects(const Node& n) const;

  cv::Point getMinCvPoint() const;

  cv::Point getMaxCvPoint() const;

  void printMe() const;

};

#endif
