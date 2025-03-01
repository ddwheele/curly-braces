#ifndef RRT_H
#define RRT_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "Node.h"
#include "Obstacle.h"
#include "Constants.h"

using namespace std;


class RRT {
public:


  RRT(Node _start, Node _goal, vector<Obstacle> _obstacles);

  void drawTree();

  void printMe() const;

private:

  cv::Mat mat;
  Node start;
  Node goal;
  vector<Obstacle> obstacles;

  void drawObstacle(const Obstacle& o) const;

  void drawNode(const Node& n, const cv::Scalar& color) const;


};

#endif
