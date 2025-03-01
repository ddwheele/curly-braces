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

cv::Point Obstacle::getMinCvPoint() const {
  return cv::Point(static_cast<int>(minx*Constants::SCALE), static_cast<int>(miny*Constants::SCALE));
}

cv::Point Obstacle::getMaxCvPoint() const {
  return cv::Point(static_cast<int>(maxx*Constants::SCALE), static_cast<int>(maxy*Constants::SCALE));
}

void Obstacle::printMe() const {
  cout << "Obstacle: ("<<minx<<","<<miny<<") to ("<<maxx<<","<<maxy<<")"<<endl;
}


