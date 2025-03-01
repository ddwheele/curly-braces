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
  RRT(shared_ptr<Node> _start, shared_ptr<Node> _goal, const vector<Obstacle> _obstacles);

  void findPath();
  void drawTree();
  void printMe() const;

private:
  cv::Mat mat;
  shared_ptr<Node> start;
  shared_ptr<Node> goal;
  vector<Obstacle> obstacles;

  void drawObstacle(const Obstacle& o) const;
  void drawNode(shared_ptr<Node>  n, const cv::Scalar& color) const;

};

#endif
