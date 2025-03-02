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
  void printMe() const;
  shared_ptr<Node> findNearest(const vector<shared_ptr<Node>>& tree, double x, double y) const;

private:
  cv::Mat mat;
  shared_ptr<Node> start;
  shared_ptr<Node> goal;
  vector<shared_ptr<Node>> startTree;
  vector<shared_ptr<Node>> goalTree;
  vector<Obstacle> obstacles;
  shared_ptr<Node> linkNode1;
  shared_ptr<Node> linkNode2;

  void drawObstacle(const Obstacle& o) const;
  void drawEndpoint(const shared_ptr<Node>& n, const cv::Scalar& color) const;
  void drawTree();
  void drawFinalPath();
  void drawNode(const shared_ptr<Node>& n, const cv::Scalar& color, int width=1) const;
};

#endif
