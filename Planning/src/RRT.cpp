#include <iostream>
#include <limits>
#include <cmath>
#include "RRT.h"

using namespace std;


RRT::RRT(shared_ptr<RrtNode> _start, shared_ptr<RrtNode> _goal, vector<Obstacle> _obstacles, double _stepSize) 
 : start(std::move(_start)), goal(std::move(_goal)), stepSize(_stepSize), obstacles(_obstacles) {
  startTree.push_back(start);
  goalTree.push_back(goal);
}

shared_ptr<RrtNode> RRT::findNearest(const vector<shared_ptr<RrtNode>>& tree, double x, double y) const {
  shared_ptr<RrtNode> ret;
  double closest = std::numeric_limits<double>::max();
  for(const auto& RrtNode : tree) {
    double dist = RrtNode->distanceTo(x, y);
    if(dist < closest) {
      closest = dist;
      ret = RrtNode;
    }
  }
  return ret;
}

bool RRT::hitsAnObstacle(const shared_ptr<RrtNode>& n) {
  for(auto& o : obstacles) {
    if(o.intersects(*n)) {
      return true;
    }
  }
  return false;
}

void RRT::findPath() {
  std::srand(std::time(0));

  bool useStartTree = true;

  for(int i=0; i<Constants::NUM_STEPS; i++) {
    // create random point
    double randX = std::rand() % static_cast<int>(Constants::WIDTH);
    double randY = std::rand() % static_cast<int>(Constants::HEIGHT);

    // find nearest RrtNode from current tree
    shared_ptr<RrtNode> nearest; 
    if(useStartTree) {
      nearest = findNearest(startTree, randX, randY); 
    } else {
      nearest = findNearest(goalTree, randX, randY); 
    }

    // Make new RrtNode and add to tree if they don't intersect obstacle
    shared_ptr<RrtNode> candidateRrtNode = RrtNode::growToward(nearest, randX, randY, stepSize);

    if(hitsAnObstacle(candidateRrtNode)) {

      continue;
    }
    shared_ptr<RrtNode> nearestOther;
    if(useStartTree) {
      startTree.push_back(candidateRrtNode);
      nearestOther = findNearest(goalTree, candidateRrtNode->x, candidateRrtNode->y);
    } else {
      goalTree.push_back(candidateRrtNode);
      nearestOther = findNearest(startTree, candidateRrtNode->x, candidateRrtNode->y);
    }

    if(!nearestOther) {
      candidateRrtNode->printMe();
    }
    //if(candidateRrtNode->distanceTo(*nearestOther) < Constants::STEP_SIZE)
    double nx = nearestOther->x;
    double ny = nearestOther->y;
    if(candidateRrtNode->distanceTo(nx, ny) < stepSize) {

      linkRrtNode1 = candidateRrtNode;
      linkRrtNode2 = nearestOther;
      cout << i << " steps" << endl;
      drawTree();
      drawFinalPath();
      return;
    }

    drawTree();

    useStartTree = !useStartTree;
  }
  cout << "Ran out of steps! " << Constants::NUM_STEPS << endl;
}

void RRT::drawFinalPath() {
  shared_ptr<RrtNode> curr = linkRrtNode1;

  while(curr && curr->parent) {
    drawRrtNode(curr, Constants::BLUE, 2);
    curr = curr->parent;
  }
  curr = linkRrtNode2;
  while(curr && curr->parent) {
    drawRrtNode(curr, Constants::BLUE, 2);
    curr = curr->parent;
  }

  cv::line(mat, linkRrtNode1->getCvPoint(), 
              linkRrtNode2->getCvPoint(),
              Constants::BLUE, 2);

  cv::imshow("Tree", mat);
  cv::waitKey(0);
} 

void RRT::drawTree() {
  mat = cv::Mat(Constants::HEIGHT_PX, Constants::WIDTH_PX, CV_8UC3, Constants::WHITE);
  for(auto& o : obstacles) {
    drawObstacle(o);
  }
  drawEndpoint(start, Constants::GREEN);
  drawEndpoint(goal, Constants::RED);

  for(auto nd : startTree) {
    if (nd->parent) {
      drawRrtNode(nd, Constants::BLACK);
    }
  }

  for(auto nd : goalTree) {
    if (nd->parent) {
      drawRrtNode(nd, Constants::BLACK);
    }
  }

  cv::imshow("Tree", mat);
  cv::waitKey(Constants::SHOW_DELAY);
}

void RRT::drawRrtNode(const shared_ptr<RrtNode>& n, const cv::Scalar& color, int width) const {
  cv::line(mat, n->getCvPoint(), 
                n->parent->getCvPoint(),
                color, width);
}

void RRT::drawEndpoint(const shared_ptr<RrtNode>& n, const cv::Scalar& color) const {
  cv::circle(mat, n->getCvPoint(), Constants::RADIUS_PX, color, -1);
}

void RRT::drawObstacle(const Obstacle& o) const {
  cv::rectangle(mat, o.getMinCvPoint(), o.getMaxCvPoint(), Constants::GRAY, -1);
}

void RRT::printMe() const {
  cout << "Start: ";
  start->printMe();
  cout << "Goal: ";
  goal->printMe();
  for(auto& o : obstacles) {
    o.printMe();
  }
}

