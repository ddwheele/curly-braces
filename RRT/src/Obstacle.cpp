#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle(double x1, double y1, double x2, double y2) {
  minx = min(x1, x2);
  maxx = max(x1, x2);
  miny = min(y1, y2);
  maxy = max(y1, y2);
}

bool Obstacle::pointIsInside(const double x, const double y) const {
  if(x >= minx && x <= maxx && y >= miny && y <= maxy) {
    return true;
  }
  return false;
}

bool Obstacle::intersects(const Node& n) const{
  if(!n.parent) {
    return pointIsInside(n.x, n.y);
  }

  double ax = min(n.x, n.parent->x);
  double ay = min(n.y, n.parent->y);
  double bx = max(n.x, n.parent->x);
  double by = max(n.y, n.parent->y);
  
  if(pointIsInside(ax,ay) || pointIsInside(bx,by)) {
    return true;
  }

  // line can't intersect obstacle
  if(bx < minx || ax > maxx || by < miny || ay > maxy) {
    return false;
  }

  if(ax < minx) {
    // find problematic slopes



  }


  return true;

}

cv::Point Obstacle::getMinCvPoint() const {
  return cv::Point(static_cast<int>(minx*Constants::SCALE), static_cast<int>(miny*Constants::SCALE));
}

cv::Point Obstacle::getMaxCvPoint() const {
  return cv::Point(static_cast<int>(maxx*Constants::SCALE), static_cast<int>(maxy*Constants::SCALE));
}

void Obstacle::printMe() const {
  cout << "Obstacle: ("<<minx<<","<<miny<<") to ("<<maxx<<","<<maxy<<")"<<endl;
}


