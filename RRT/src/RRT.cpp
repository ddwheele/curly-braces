#include <iostream>

#include "RRT.h"

using namespace std;


RRT::RRT(Node _start, Node _goal, vector<Obstacle> _obstacles) 
 : start(_start), goal(_goal), obstacles(_obstacles) {
}

void RRT::drawTree() {
  mat = cv::Mat(Constants::HEIGHT_PX, Constants::WIDTH_PX, CV_8UC3, Constants::WHITE);
  for(auto& o : obstacles) {
    drawObstacle(o);
  }
  drawNode(start, Constants::GREEN);
  drawNode(goal, Constants::RED);
  cv::imshow("Tree", mat);
  cv::waitKey(0);
}

void RRT::drawNode(const Node& n, const cv::Scalar& color) const {
  cv::circle(mat, n.getCvPoint(), Constants::RADIUS_PX, color, -1);
}

void RRT::drawObstacle(const Obstacle& o) const {
  cv::rectangle(mat, o.getMinCvPoint(), o.getMaxCvPoint(), Constants::GRAY, -1);
}

void RRT::printMe() const {
  cout << "Start: ";
  start.printMe();
  cout << "Goal: ";
  goal.printMe();
  for(auto& o : obstacles) {
    o.printMe();
  }
}

