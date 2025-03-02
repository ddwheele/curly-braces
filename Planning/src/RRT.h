#ifndef RRT_H
#define RRT_H

#include <memory>
#include <opencv2/opencv.hpp>
#include "RrtNode.h"
#include "Obstacle.h"
#include "Constants.h"

using namespace std;

class RRT {
public:
  RRT(shared_ptr<RrtNode> _start, shared_ptr<RrtNode> _goal, const vector<Obstacle> _obstacles, double _stepSize=0.2);

  void findPath();
  void printMe() const;
  shared_ptr<RrtNode> findNearest(const vector<shared_ptr<RrtNode>>& tree, double x, double y) const;

private:
  cv::Mat mat;
  shared_ptr<RrtNode> start;
  shared_ptr<RrtNode> goal;
  vector<shared_ptr<RrtNode>> startTree;
  vector<shared_ptr<RrtNode>> goalTree;
  vector<Obstacle> obstacles;
  shared_ptr<RrtNode> linkRrtNode1;
  shared_ptr<RrtNode> linkRrtNode2;
  double stepSize;

  void drawObstacle(const Obstacle& o) const;
  void drawEndpoint(const shared_ptr<RrtNode>& n, const cv::Scalar& color) const;
  void drawTree();
  void drawFinalPath();
  void drawRrtNode(const shared_ptr<RrtNode>& n, const cv::Scalar& color, int width=1) const;
  bool hitsAnObstacle(const shared_ptr<RrtNode>& n);
};

#endif