#include <iostream>

#include "RRT.hpp"

using namespace std;


RRT::RRT(Node _start, Node _goal, vector<Obstacle> _obstacles) 
 : start(_start), goal(_goal), obstacles(_obstacles) {
  mat = cv::Mat(HEIGHT, WIDTH, CV_8UC3, WHITE);

}

void RRT::drawTree() {

}

void RRT::printMe() {
  cout << "Start: ";
  start.printMe();
  cout << "Goal: ";
  goal.printMe();
  for(auto& o : obstacles) {
    o.printMe();
  }
}

const cv::Scalar RRT::WHITE(255, 255, 255);
const cv::Scalar RRT::BLACK(0, 0, 0);
const cv::Scalar RRT::RED(0, 0, 255);
const cv::Scalar RRT::GREEN(0, 255, 0);
const cv::Scalar RRT::BLUE(255, 0, 0);
const cv::Scalar RRT::GRAY(100, 100, 100);