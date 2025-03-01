#ifndef RRT_HPP
#define RRT_HPP

#include <memory>
#include <opencv2/opencv.hpp>
#include "utils.h"

using namespace std;


class RRT {
public:
  RRT(Node _start, Node _goal, vector<Obstacle> _obstacles);

  void drawTree();

  void printMe();

private:
  const int HEIGHT = 500;
  const int WIDTH = 500;
  const int STEP_SIZE = 10;
  const int RADIUS = 5;
  cv::Mat mat;
  Node start;
  Node goal;
  vector<Obstacle> obstacles;

  static const cv::Scalar WHITE;
  static const cv::Scalar BLACK;
  static const cv::Scalar RED;
  static const cv::Scalar GREEN;
  static const cv::Scalar BLUE;
  static const cv::Scalar GRAY;


};

#endif
