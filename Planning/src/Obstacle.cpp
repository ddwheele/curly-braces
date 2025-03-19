#include <memory>
#include <algorithm>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Utils.h"
#include "Obstacle.h"

using namespace std;

Obstacle::Obstacle(const double x1, const double y1, const double x2, const double y2) {
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

bool Obstacle::intersects(const RrtNode& n) const{
  // no parent or parent is same point
  if(!n.parent || (Utils::equals(n.x, n.parent->x) && Utils::equals(n.y, n.parent->y))) {
    return pointIsInside(n.x, n.y);
  }

  // n has parent, check if either end is inside
  if(pointIsInside(n.x, n.y) || pointIsInside(n.parent->x,n.parent->y)) {
    return true;
  }

  double lx, ly, rx, ry; // label as left and right points
  if(n.x < n.parent->x) {
    // point is lefter
    lx = n.x;
    ly = n.y;
    rx = n.parent->x;
    ry = n.parent->y;
  } else if(n.x > n.parent->x) {
    rx = n.x;
    ry = n.y;
    lx = n.parent->x;
    ly = n.parent->y;
  } else {
    // line is vertical, label as upper and lower
    double tx,ty, bx, by;
    if(n.y > n.parent->y) {
      tx = n.x;
      ty = n.y;
      bx = n.parent->x;
      by = n.parent->y;
    } else {
      bx = n.x;
      by = n.y;
      tx = n.parent->x;
      ty = n.parent->y;
    }
    // vertical line can't intersect obstacle
    if(ty < miny || by > maxy || (tx < minx) || (tx > maxx)) {
      return false;
    }
    // vertical line must straddle obstacle
    return true;
  }

  // line can't intersect obstacle
  if(rx < minx || lx > maxx || (ly < miny && ry < miny) || (ly > maxy && ry > maxy)) {
    return false;
  }

  // TODO: cases where boundary slope is vertical
  if(Utils::equals(lx,minx) || Utils::equals(lx,maxx)) {
    cout << "Unimplemented case" << endl;
  }

  // divide into ninths and find boundary slopes
  double actualSlope = (ly-ry) / (lx-rx);
  if(lx < minx) {
    double upperSlope, lowerSlope;
    if(ly > maxy) {
      // upper left ninth
      // upper slope intersects maxx, maxy
      // lower slope intersects minx, miny
      upperSlope = (ly-maxy) / (lx-maxx);
      lowerSlope = (ly-miny) / (lx-minx);
    } else if(ly < miny) {
      // lower left ninth
      // upper slope intersects minx, maxy
      // lower slope intersects maxx, miny
      upperSlope = (ly-maxy) / (lx-minx);
      lowerSlope = (ly-miny) / (lx-maxx);
    } else {
      // straight to the left
      // problem if < (minx, maxy) AND > (minx, miny)
      upperSlope = (ly-maxy) / (lx-minx);
      lowerSlope = (ly-miny) / (lx-minx);
    }
   if(actualSlope < upperSlope && actualSlope > lowerSlope) {
     return true;
   }
  } else if(lx < maxx) { // in middle column
    if(ly > maxy) {
      // straight above
      // relevant corner is maxx, maxy
      double minSlope = (ly-maxy) / (lx-maxx);

      if(actualSlope < minSlope) {
       return true;
      }
    } else { // must be below, or point would be inside
      // straight below
      // relevant corner is maxx, miny
      double maxSlope = (ly-miny) / (lx-maxx);
      
      if(actualSlope > maxSlope) {
        return true;
      }
    }
  } // already handled where ax > maxx

  return false;
}

cv::Point Obstacle::getMinCvPoint() const {
  return cv::Point(static_cast<int>(minx*Utils::SCALE), static_cast<int>(miny*Utils::SCALE));
}

cv::Point Obstacle::getMaxCvPoint() const {
  return cv::Point(static_cast<int>(maxx*Utils::SCALE), static_cast<int>(maxy*Utils::SCALE));
}

void Obstacle::printMe() const {
  cout << "Obstacle: ("<<minx<<","<<miny<<") to ("<<maxx<<","<<maxy<<")"<<endl;
}


