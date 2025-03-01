#include <iostream>

#include "RRT.hpp"

using namespace std;

const cv::Scalar RRT::WHITE(255, 255, 255);
const cv::Scalar RRT::BLACK(0, 0, 0);
const cv::Scalar RRT::RED(0, 0, 255);
const cv::Scalar RRT::GREEN(0, 255, 0);
const cv::Scalar RRT::BLUE(255, 0, 0);
const cv::Scalar RRT::GRAY(100, 100, 100);


RRT::RRT() {
  // do something here
  mat = cv::Mat(HEIGHT, WIDTH, CV_8UC3, WHITE);
}

void RRT::drawTree() {

}



void RRT::printSomething() {
  cout << "Der Wind weht durch meine Aeste." << endl;
}
